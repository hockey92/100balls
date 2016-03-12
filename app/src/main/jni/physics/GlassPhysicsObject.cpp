#include <vecmath.h>
#include "GlassPhysicsObject.h"
#include "GlassShape.h"
#include "Constants.h"
#include "common.hpp"
#include "ScoreService.h"

GlassPhysicsObject::GlassPhysicsObject(GlassPath *glassPath) : PhysicsObject(new GlassShape(), 0.f),
                                                               child(NULL),
                                                               parent(NULL),
                                                               isRotate(false),
                                                               glassPath(glassPath),
                                                               numOfCircles(0),
                                                               wasted(false),
                                                               numOfGlassesToParent(1),
                                                               score(0) {
    for (int i = 0; i < 3; i++) {
        lines[i] = new Line(
                ((Segment *) getShape()->getChildren(i))->getPoint(0),
                ((Segment *) getShape()->getChildren(i))->getPoint(1)
        );
    }
    lines[3] = new Line(
            ((Segment *) getShape()->getChildren(2))->getPoint(1),
            ((Segment *) getShape()->getChildren(0))->getPoint(0)
    );
    getShape()->move(glassPath->getStartPoint());
    updatePositionOnPath();
    initVelValue = -0.5f;
}

GlassPhysicsObject::~GlassPhysicsObject() {
    for (int i = 0; i < 4; i++) {
        delete lines[i];
    }
}

void GlassPhysicsObject::update() {
    if (!parent && !wasted) {
        innerUpdate();
    }
}

void GlassPhysicsObject::setChild(GlassPhysicsObject *child) {
    this->child = child;
    child->setParent(this);
}

void GlassPhysicsObject::setParent(GlassPhysicsObject *parent) {
    this->parent = parent;
}

void GlassPhysicsObject::innerUpdate() {
    if (!parent) {
        clearVel = ScoreService::getInstance()->getGlassVel();
    } else {
        float parentPositionOnPath = parent->positionOnPath;
        float distanceFromParent = glassPath->getDistanceBetweenPoints(parentPositionOnPath,
                                                                       positionOnPath);
        float parentClearVel = parent->clearVel;
        clearVel = parentClearVel -
                   0.01f * (distanceFromParent -
                            glassPath->getDistanceBetweenGlasses() * numOfGlassesToParent) / DT;
    }

    setVel((Vec2::cross(normal, 1) * clearVel) +
           (normal * (((len - glassPath->getDistFromPath()) * 0.1f) / DT)));

    float startRotatePoint = glassPath->getPointOnPath(6);
    float stopRotatePoint = glassPath->getPointOnPath(7);
    float angleVel = (2.0f * PI) / (DT * ((stopRotatePoint - startRotatePoint) / (clearVel * DT)));
    if (startRotatePoint <= positionOnPath && positionOnPath <= stopRotatePoint) {
        if (!isRotate) {
            setAngleVel(angleVel);
            isRotate = true;
        }
    } else {
        isRotate = false;
    }

    if (getShape()->getAngel() < -2.0f * PI) {
        getShape()->rotate(-getShape()->getAngel());
        setAngleVel(0.0f);
    }

    if (child) {
        child->innerUpdate();
    }
}

bool GlassPhysicsObject::containsPoint(const Vec2 &point) const {
    Vec2 relPoint = point - getShape()->getCenter();
    for (int i = 0; i < 4; i++) {
        if (lines[i]->getValue(relPoint) < 0) {
            return false;
        }
    }
    return true;
}

bool GlassPhysicsObject::containsCircles() {
    return !circles.empty();
}

void GlassPhysicsObject::clearCircles() {
    circles.clear();
}

void GlassPhysicsObject::addCircle(CirclePhysicsObject *circlePhysicsObject) {
    circles.push_back(circlePhysicsObject);
    if (glassPath->isDown(normal)) {
        if (0 <= score && score < 50) {
            score += 1;
            ScoreService::getInstance()->add(1);
        } else if (50 <= score && score < 100) {
            score += 2;
            ScoreService::getInstance()->add(2);
        } else if (100 <= score) {
            score += 5;
            ScoreService::getInstance()->add(5);
        }
        score++;
    }
}

GlassPhysicsObject *GlassPhysicsObject::getTail() {
    if (child != NULL) {
        return child->getTail();
    }
    return this;
}

GlassPhysicsObject *GlassPhysicsObject::getHead() {
    if (parent != NULL) {
        return parent->getHead();
    }
    return this;
}

void GlassPhysicsObject::updatePos() {
    PhysicsObject::updatePos();
    if (getShape() != NULL) {
        if (getShape()->getCenter().x() < -2.0f) {
            setDeleted(true);
            return;
        }
        updatePositionOnPath();
    }
}

void GlassPhysicsObject::updatePositionOnPath() {
    positionOnPath = glassPath->getPositionOnPath(getShape()->getCenter(), len, normal);
}

void GlassPhysicsObject::doActionAfter() {
    if (wasted) {
        return;
    }

    if (glassPath->isLeft(normal) && !containsCircles()) {
        waste();
    } else if (glassPath->isRight(normal) && containsCircles()) {
        clearCircles();
    }
}

void GlassPhysicsObject::waste() {
    wasted = true;
    if (parent) {
        parent->child = child;
    }
    if (child) {
        child->parent = parent;
        child->numOfGlassesToParent += numOfGlassesToParent;
    }
    parent = NULL;
    child = NULL;
    setVel(Vec2(initVelValue, 0.0f));
}

void GlassPhysicsObject::draw(float *projMat, Shader *simpleShader) {
    BaseShape *shape = getShape();
    Vec2 center = shape->getCenter();
    simpleShader->setMVP((ndk_helper::Mat4(projMat) *
                          ndk_helper::Mat4::Translation(center.x(), center.y(),
                                                        0.0f) *
                          ndk_helper::Mat4::RotationZ(-shape->getAngel())).Ptr());
    if (0 <= score && score < 50) {
        simpleShader->setColor(1.0f, 1.0f, 1.0f, 0.5f);
    } else if (50 <= score && score < 100) {
        simpleShader->setColor(1.0f, 0.0f, 0.0f, 0.5f);
    } else if (100 <= score && score < 150) {
        simpleShader->setColor(0.0f, 1.0f, 0.0f, 0.5f);
    } else if (150 <= score) {
        simpleShader->setColor(1.0f, 0.0f, 1.0f, 0.5f);
    }
    GLushort indices1[] = {0, 1, 2, 0, 2, 3};
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices1);
    simpleShader->setColor(0.0f, 0.0f, 0.0f, 1.0f);
    GLushort indices2[] = {0, 1, 1, 2, 2, 3};
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, indices2);
}