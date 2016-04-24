#include <vecmath.h>
#include "GlassGameObject.h"
#include "GlassShape.h"
#include "Constants.h"
#include "common.hpp"
#include "ScoreService.h"
#include "SimpleInitializer.h"
#include "Context.h"

GlassGameObject::GlassGameObject(GlassPath *glassPath) : GameObject(new GlassShape(), 0.f),
                                                         child(NULL),
                                                         parent(NULL),
                                                         isRotate(false),
                                                         glassPath(glassPath),
                                                         numOfCircles(0),
                                                         wasted(false),
                                                         numOfGlassesToParent(1),
                                                         score(0),
                                                         color(Color(1.0f, 1.0f, 1.0f, 1.0f)) {
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

    reset();
}

GlassGameObject::~GlassGameObject() {
    for (int i = 0; i < 4; i++) {
        delete lines[i];
    }
}

void GlassGameObject::update() {
    if (!parent && !wasted) {
        innerUpdate();
    }
}

void GlassGameObject::setChild(GlassGameObject *child) {
    this->child = child;
    child->setParent(this);
}

void GlassGameObject::setParent(GlassGameObject *parent) {
    this->parent = parent;
}

void GlassGameObject::innerUpdate() {
    if (!parent) {
        clearVel = Context::getInstance()->getScoreService()->getGlassVel();
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

bool GlassGameObject::containsPoint(const Vec2 &point) const {
    Vec2 relPoint = point - getShape()->getCenter();
    for (int i = 0; i < 4; i++) {
        if (lines[i]->getValue(relPoint) < 0) {
            return false;
        }
    }
    return true;
}

bool GlassGameObject::containsCircles() {
    return !circles.empty();
}

void GlassGameObject::clearCircles() {
    circles.clear();
}

void GlassGameObject::addCircle(CircleGameObject *circlePhysicsObject) {
    circles.push_back(circlePhysicsObject);
    if (glassPath->isDown(normal)) {
        if (0 <= score && score < 50) {
            score += 1;
            Context::getInstance()->getScoreService()->add(1);
        } else if (50 <= score && score < 100) {
            score += 2;
            Context::getInstance()->getScoreService()->add(2);
        } else if (100 <= score) {
            score += 5;
            Context::getInstance()->getScoreService()->add(5);
        }
        score++;
    }
    bool changeColor = true;
    if (0 <= score && score < 50) {
        changeColor = false;
        color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    } else if (50 <= score && score < 100) {
        color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    } else if (100 <= score && score < 150) {
        color = Color(0.0f, 1.0f, 0.0f, 1.0f);
    } else if (150 <= score) {
        color = Color(1.0f, 0.0f, 1.0f, 1.0f);
    }
    if (changeColor) {
        for (std::list<CircleGameObject *>::iterator iter = circles.begin();
             iter != circles.end(); ++iter) {
            (*iter)->setColor(color);
        }
    }
}

GlassGameObject *GlassGameObject::getTail() {
    if (child != NULL) {
        return child->getTail();
    }
    return this;
}

GlassGameObject *GlassGameObject::getHead() {
    if (parent != NULL) {
        return parent->getHead();
    }
    return this;
}

void GlassGameObject::updatePos() {
    PhysicsObject::updatePos();
    if (getShape() != NULL) {
        if (getShape()->getCenter().x() < -2.0f) {
            setDeleted(true);
            return;
        }
        updatePositionOnPath();
    }
}

void GlassGameObject::updatePositionOnPath() {
    positionOnPath = glassPath->getPositionOnPath(getShape()->getCenter(), len, normal);
}

void GlassGameObject::doActionAfter() {
    if (wasted) {
        return;
    }

    if (glassPath->isLeft(normal) && !containsCircles()) {
        waste();
    } else if (glassPath->isRight(normal) && containsCircles()) {
        clearCircles();
    }
}

void GlassGameObject::waste() {
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

void GlassGameObject::draw(const DrawableData &drawableDate) {

    Shader *simpleShader = drawableDate.simpleShader;
    float *projMat = drawableDate.projMat;

    BaseShape *shape = getShape();
    Vec2 center = shape->getCenter();
    simpleShader->setMVP((ndk_helper::Mat4(projMat) *
                          ndk_helper::Mat4::Translation(center.x(), center.y(), 0.0f) *
                          ndk_helper::Mat4::RotationZ(-shape->getAngel())).Ptr());
    simpleShader->setColor(color.r(), color.g(), color.b(), 0.5f);

    GLushort indices1[] = {0, 1, 2, 0, 2, 3};
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices1);
    simpleShader->setColor(color);

    GLushort indices2[] = {0, 1, 1, 2, 2, 3};
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, indices2);
}

unsigned int GlassGameObject::type() {
    return getShape()->type();
}

void GlassGameObject::reset() {
    child = NULL;
    parent = NULL;
    isRotate = false;
    numOfCircles = 0;
    wasted = false;
    numOfGlassesToParent = 1;
    score = 0;
    color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    initVelValue = -0.5f;
    BaseShape *shape = getShape();
    shape->setCenter(glassPath->getGlassStartPoint());
    shape->rotate(shape->getAngel());
    setDeleted(false);
    updatePositionOnPath();
}
