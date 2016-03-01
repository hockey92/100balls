#include "GlassPhysicsObject.h"
#include "GlassShape.h"
#include "Constants.h"
#include "common.hpp"

GlassPhysicsObject::GlassPhysicsObject(GlassPath *glassPath) : PhysicsObject(new GlassShape(), 0.f),
                                                               child(NULL),
                                                               parent(NULL),
                                                               isRotate(false),
                                                               glassPath(glassPath),
                                                               numOfCircles(0) {
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
}

GlassPhysicsObject::~GlassPhysicsObject() {
    for (int i = 0; i < 4; i++) {
        delete lines[i];
    }
}

void GlassPhysicsObject::update() {
    if (!parent) {
        innerUpdate();
    }
}

void GlassPhysicsObject::setChildren(GlassPhysicsObject *children) {
    this->child = children;
    children->setParent(this);
}

void GlassPhysicsObject::setParent(GlassPhysicsObject *parent) {
    this->parent = parent;
}

void GlassPhysicsObject::innerUpdate() {
    float initVelValue = -0.5f;

    float len;
    Vec2 normal;

    positionOnPath = glassPath->getPositionOnPath(getShape()->getCenter(), len, normal);

    if (!parent) {
        clearVel = initVelValue;
    } else {
        float parentPositionOnPath = parent->positionOnPath;
        float distanceFromParent = glassPath->getDistanceBetweenPoints(parentPositionOnPath,
                                                                       positionOnPath);
        float parentClearVel = parent->clearVel;
        clearVel = parentClearVel -
                   0.01f * (distanceFromParent - glassPath->getDistanceBetweenGlasses()) / DT;
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


//    if (!parent) {
//        LOGE("values %f", getPositionOnPath(normal, point));
//    }

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

void GlassPhysicsObject::clear() {
    circles.clear();
}

void GlassPhysicsObject::addCircle(CirclePhysicsObject *circlePhysicsObject) {
    circles.push_back(circlePhysicsObject);
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
