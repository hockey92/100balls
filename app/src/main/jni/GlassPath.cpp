#include "GlassPath.h"
#include "Context.h"
#include "Constants.h"
#include "CollisionFactory.h"

GlassPath::GlassPath() {
    left = -0.6f;
    down = -Context::getInstance()->getH() + 0.44f;
    right = 0.6f;
    up = Context::getInstance()->getH() - 0.44f;

    distFromPath = 0.2f;

    path[0] = new Segment(Vec2(right, up), Vec2(right, down));
    path[1] = new Segment(Vec2(right, down), Vec2(left, down));
    path[2] = new Segment(Vec2(left, down), Vec2(left, up));
    path[3] = new Segment(Vec2(left, up), Vec2(right, up));

    quartOfCircleLen = PI * distFromPath / 2.0f;

    numOfGlasses = 7;

    h = up - down;
    w = right - left;
    pointsOnPath[0] = 0;
    pointsOnPath[1] = h;
    pointsOnPath[2] = h + quartOfCircleLen;
    pointsOnPath[3] = h + w + quartOfCircleLen;
    pointsOnPath[4] = h + w + 2.0f * quartOfCircleLen;
    pointsOnPath[5] = 2.0f * h + w + 2.0f * quartOfCircleLen;
    pointsOnPath[6] = 2.0f * h + w + 3.0f * quartOfCircleLen;
    pointsOnPath[7] = 2.0f * h + 2.0f * w + 3.0f * quartOfCircleLen;
    pointsOnPath[8] = 2.0f * h + 2.0f * w + 4.0f * quartOfCircleLen;

    pathLen = pointsOnPath[8];
    distanceBetweenGlasses = pathLen / 7.0f;
}

float GlassPath::getPositionOnPath(const Vec2 &center, float &len, Vec2 &normal) const {
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

    float x = point.x(), y = point.y();

    if (isRight(normal)) {
        return pointsOnPath[0] + (up - y);
    } else if (isDown(normal)) {
        return pointsOnPath[2] + (right - x);
    } else if (isLeft(normal)) {
        return pointsOnPath[4] + (y - down);
    } else if (isUp(normal)) {
        return pointsOnPath[6] + (x - left);
    }

    float currentAngle = atanf(fabsf(normal.y()) / fabsf(normal.x()));

    if (isDownRightCurve(normal)) {
        return pointsOnPath[1] + quartOfCircleLen * (currentAngle / (PI / 2.0f));
    } else if (isDownLeftCurve(normal)) {
        return pointsOnPath[3] + quartOfCircleLen * (1 - currentAngle / (PI / 2.0f));
    } else if (isUpLeftCurve(normal)) {
        return pointsOnPath[5] + quartOfCircleLen * (currentAngle / (PI / 2.0f));
    } else if (isUpRightCurve(normal)) {
        return pointsOnPath[7] + quartOfCircleLen * (1 - currentAngle / (PI / 2.0f));
    }

    return 0;
}

bool GlassPath::isZero(float value) const {
    float d = 0.001f;
    return value < d && value > -d;
}

bool GlassPath::isRight(const Vec2 &normal) const {
    float x = normal.x(), y = normal.y();
    bool isXZero = isZero(x), isYZero = isZero(y);
    return !isXZero && x < 0 && isYZero;
}

bool GlassPath::isDownRightCurve(const Vec2 &normal) const {
    float x = normal.x(), y = normal.y();
    bool isXZero = isZero(x), isYZero = isZero(y);
    return x < 0 && y > 0 && !isXZero && !isYZero;
}

bool GlassPath::isDown(const Vec2 &normal) const {
    float x = normal.x(), y = normal.y();
    bool isXZero = isZero(x), isYZero = isZero(y);
    return isXZero && !isYZero && y > 0;
}

bool GlassPath::isDownLeftCurve(const Vec2 &normal) const {
    float x = normal.x(), y = normal.y();
    bool isXZero = isZero(x), isYZero = isZero(y);
    return x > 0 && y > 0 && !isXZero && !isYZero;
}

bool GlassPath::isLeft(const Vec2 &normal) const {
    float x = normal.x(), y = normal.y();
    bool isXZero = isZero(x), isYZero = isZero(y);
    return !isXZero && x > 0 && isYZero;
}

bool GlassPath::isUpLeftCurve(const Vec2 &normal) const {
    float x = normal.x(), y = normal.y();
    bool isXZero = isZero(x), isYZero = isZero(y);
    return x > 0 && y < 0 && !isXZero && !isYZero;
}

bool GlassPath::isUp(const Vec2 &normal) const {
    float x = normal.x(), y = normal.y();
    bool isXZero = isZero(x), isYZero = isZero(y);
    return isXZero && !isYZero && y < 0;
}

bool GlassPath::isUpRightCurve(const Vec2 &normal) const {
    float x = normal.x(), y = normal.y();
    bool isXZero = isZero(x), isYZero = isZero(y);
    return x < 0 && y < 0 && !isXZero && !isYZero;
}

float GlassPath::getPointOnPath(int i) const {
    return pointsOnPath[i];
}

float GlassPath::getDistanceBetweenGlasses() const {
    return distanceBetweenGlasses;
}

float GlassPath::getPathLen() const {
    return pathLen;
}

float GlassPath::getDistFromPath() const {
    return distFromPath;
}

float GlassPath::getDistanceBetweenPoints(const Vec2 &point1, const Vec2 &point2) const {
    float len;
    Vec2 normal;
    float positionOnPath1 = getPositionOnPath(point1, len, normal);
    float positionOnPath2 = getPositionOnPath(point2, len, normal);
    return getDistanceBetweenPoints(positionOnPath1, positionOnPath2);
}

float GlassPath::getDistanceBetweenPoints(float point1, float point2) const {
    float distanceBetweenPoints = point1 >= point2 ? point1 - point2 : point1 + (pathLen - point2);
    return distanceBetweenPoints;
}

Vec2 GlassPath::getStartPoint() const {
    return Vec2(right + distFromPath + 0.5f, -h / 4.0f);
}
