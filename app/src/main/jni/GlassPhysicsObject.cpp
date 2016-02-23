#include "GlassPhysicsObject.h"
#include "GlassShape.h"
#include "CollisionFactory.h"
#include "Constants.h"
#include "common.hpp"
#include "GameCoords.h"

GlassPhysicsObject::GlassPhysicsObject() : PhysicsObject(new GlassShape(), 0.f), children(NULL),
                                           parent(NULL) {
    right = GameCoords::getInstance()->getCoords(PATH)->getData()[RIGHT];
    left = GameCoords::getInstance()->getCoords(PATH)->getData()[LEFT];
    down = GameCoords::getInstance()->getCoords(PATH)->getData()[DOWN];
    up = GameCoords::getInstance()->getCoords(PATH)->getData()[UP];

    distFromPath = GameCoords::getInstance()->getCoords(PATH)->getData()[DIST_FROM_PATH];

    path[0] = new Segment(Vec2(right, up), Vec2(right, down));
    path[1] = new Segment(Vec2(right, down), Vec2(left, down));
    path[2] = new Segment(Vec2(left, down), Vec2(left, up));
    path[3] = new Segment(Vec2(left, up), Vec2(right, up));
}

void GlassPhysicsObject::update() {
    if (!parent) {
        innerUpdate();
    }
}

void GlassPhysicsObject::setChildren(GlassPhysicsObject *children) {
    this->children = children;
    children->setParent(this);
}

void GlassPhysicsObject::setParent(GlassPhysicsObject *parent) {
    this->parent = parent;
}

void GlassPhysicsObject::innerUpdate() {
    float initVelValue = -0.8f;
    pathLen = 2.0f * (up - down) + 2.0f * (right - left) + 2.0f * PI * distFromPath;
    float distanceBetweenTwoGlasses = pathLen / 7.0f;

    Vec2 dist;
    float len = 0;
    Vec2 point;
    for (int i = 0; i < 4; i++) {
        Vec2 tempPoint;
        Vec2 tempDist = CollisionFactory::createDistance(getShape()->getCenter(), path[i],
                                                         tempPoint);
        float tempLen = tempDist.len();
        if (i == 0 || tempLen < len) {
            dist = tempDist;
            len = tempLen;
            point = tempPoint;
        }
    }
    Vec2 normal = dist * (1 / len);
    positionOnPath = getPositionOnPath(normal, point);

    if (!parent) {
        clearVel = initVelValue;
    } else {
        float parentPositionOnPath = parent->positionOnPath;
        float distanceFromParent = parentPositionOnPath >= positionOnPath
                                   ? parentPositionOnPath - positionOnPath
                                   : parentPositionOnPath + (pathLen - positionOnPath);
        float parentClearVel = parent->clearVel;
        clearVel = parentClearVel - 0.01f * (distanceFromParent - distanceBetweenTwoGlasses) / DT;
    }

    setVel((Vec2::cross(normal, 1) * clearVel) + (normal * (((len - distFromPath) * 0.1f) / DT)));

//    if (!parent) {
//        LOGE("values %f", getPositionOnPath(normal, point));
//    }

    if (children) {
        children->innerUpdate();
    }
}

float GlassPhysicsObject::getPositionOnPath(Vec2 normal, Vec2 point) {
    float x = normal.x(), y = normal.y();
    bool isXZero = isZero(x), isYZero = isZero(y);
    float quartOfCircleLen = PI * distFromPath / 2.0f;
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
