#include "GlassPhysicsObject.h"
#include "GlassShape.h"
#include "CollisionFactory.h"
#include "Constants.h"
#include "common.hpp"
#include "GameCoords.h"

GlassPhysicsObject::GlassPhysicsObject() : PhysicsObject(new GlassShape(), 0.f), child(NULL),
                                           parent(NULL), isRotate(false), numOfCircles(0) {
    right = GameCoords::getInstance()->getCoords(PATH)->getData()[RIGHT];
    left = GameCoords::getInstance()->getCoords(PATH)->getData()[LEFT];
    down = GameCoords::getInstance()->getCoords(PATH)->getData()[DOWN];
    up = GameCoords::getInstance()->getCoords(PATH)->getData()[UP];

    distFromPath = GameCoords::getInstance()->getCoords(PATH)->getData()[DIST_FROM_PATH];

    path[0] = new Segment(Vec2(right, up), Vec2(right, down));
    path[1] = new Segment(Vec2(right, down), Vec2(left, down));
    path[2] = new Segment(Vec2(left, down), Vec2(left, up));
    path[3] = new Segment(Vec2(left, up), Vec2(right, up));

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
    pathLen = 2.0f * (up - down) + 2.0f * (right - left) + 2.0f * PI * distFromPath;
    quartOfCircleLen = PI * distFromPath / 2.0f;
    float distanceBetweenGlasses = pathLen / 7.0f;

    float len;
    Vec2 normal;

    positionOnPath = getPositionOnPath(getShape()->getCenter(), len, normal);

    if (!parent) {
        clearVel = initVelValue;
    } else {
        float parentPositionOnPath = parent->positionOnPath;
        float distanceFromParent = parentPositionOnPath >= positionOnPath
                                   ? parentPositionOnPath - positionOnPath
                                   : parentPositionOnPath + (pathLen - positionOnPath);
        float parentClearVel = parent->clearVel;
        clearVel = parentClearVel - 0.01f * (distanceFromParent - distanceBetweenGlasses) / DT;
    }

    setVel((Vec2::cross(normal, 1) * clearVel) + (normal * (((len - distFromPath) * 0.1f) / DT)));

    float startRotatePoint = (up - down) * 2.0f + (right - left) + quartOfCircleLen * 3.0f;
    float stopRotatePoint = (up - down) * 2.0f + (right - left) * 2.0f + quartOfCircleLen * 3.0f;
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

float GlassPhysicsObject::getPositionOnPath(const Vec2 &center, float &len, Vec2 &normal) {
    Vec2 dist;
    len = 0;
    Vec2 point;
    for (int i = 0; i < 4; i++) {
        Vec2 tempPoint;
        Vec2 tempDist = CollisionFactory::createDistance(center, path[i], tempPoint);
        float tempLen = tempDist.len();
        if (i == 0 || tempLen < len) {
            dist = tempDist;
            len = tempLen;
            point = tempPoint;
        }
    }
    normal = dist * (1 / len);

    float x = normal.x(), y = normal.y();
    bool isXZero = isZero(x), isYZero = isZero(y);
    if (!isXZero && x < 0 && isYZero) {
        return up - point.y();
    } else if (isXZero && !isYZero && y > 0) {
        return (up - down) + quartOfCircleLen + (right - point.x());
    } else if (!isXZero && x > 0 && isYZero) {
        return (up - down) + (right - left) + 2 * quartOfCircleLen + (point.y() - down);
    } else if (isXZero && !isYZero && y < 0) {
        return (up - down) * 2 + (right - left) + 3 * quartOfCircleLen + (point.x() - left);
    }

    float currentAngle = atanf(fabsf(y) / fabsf(x));

    if (x < 0 && y > 0) {
        return (up - down) + quartOfCircleLen * (currentAngle / (PI / 2.0f));
    } else if (x > 0 && y > 0) {
        return (up - down) + (right - left) + quartOfCircleLen +
               quartOfCircleLen * (1 - currentAngle / (PI / 2.0f));
    } else if (x > 0 && y < 0) {
        return (up - down) * 2.0f + (right - left) + quartOfCircleLen * 2.0f +
               quartOfCircleLen * (currentAngle / (PI / 2.0f));
    } else if (x < 0 && y < 0) {
        return (up - down) * 2.0f + (right - left) * 2.0f + quartOfCircleLen * 3.0f +
               quartOfCircleLen * (1 - currentAngle / (PI / 2.0f));
    }

    return 0;
}

bool GlassPhysicsObject::isZero(float value) {
    float d = 0.001f;
    return value < d && value > -d;
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

float GlassPhysicsObject::getDistanceBetweenGlasses(GlassPhysicsObject *glass1,
                                                    GlassPhysicsObject *glass2) {
    return 0;
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
