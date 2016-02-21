#include "GlassPhysicsObject.h"
#include "GlassShape.h"
#include "CollisionFactory.h"
#include "Constants.h"
#include "common.hpp"

GlassPhysicsObject::GlassPhysicsObject() : PhysicsObject(new GlassShape(), 0.f), children(NULL),
                                           parent(NULL) {
    right = 1.5f;
    left = -1.5f;
    down = -3;
    up = 1.0f;

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
    float initVelValue = -1.5f;
    distFromPath = 0.3f;
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


    float velValue = initVelValue;
    setVel((Vec2::cross(normal, 1) * velValue) + (normal * (((len - distFromPath) * 0.1f) / DT)));

    LOGE("values %f", getPositionOnPath(normal, point));

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
        return (up - down) * 2 + (right - left) + 2 * quartOfCircleLen + (point.x() - left);
    }

    float absX = fabsf(x), absY = fabsf(y);
    float currentAngle = atanf(absY / absX);

    if (x > 0 && isYZero) {

    } else if (isXZero && y < 0) {

    } else if (x < 0 && isYZero) {

    } else if (isXZero && y > 0) {

    }

    return 0;
}

bool GlassPhysicsObject::isZero(float value) {
    float d = 0.0001f;
    return value < d && value > -d;
}
