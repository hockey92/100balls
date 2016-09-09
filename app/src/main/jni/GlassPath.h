#ifndef NATIVE_ACTIVITY_GLASSOBJECTSCONSTANTS_H
#define NATIVE_ACTIVITY_GLASSOBJECTSCONSTANTS_H

#include "Segment.h"

class GlassPath {
public:
    GlassPath();

    float getPositionOnPath(const Vec2 &center, float &len, Vec2 &normal) const;

    float getDistanceBetweenPoints(const Vec2 &point1, const Vec2 &point2) const;

    float getDistanceBetweenPoints(float point1, float point2) const;

    float getPointOnPath(int i) const;

    float getDistanceBetweenGlasses() const;

    float getPathLen() const;

    float getDistFromPath() const;

    Vec2 getGlassStartPoint() const;

    bool isRight(const Vec2 &normal) const;

    bool isDownRightCurve(const Vec2 &normal) const;

    bool isDown(const Vec2 &normal) const;

    bool isDownLeftCurve(const Vec2 &normal) const;

    bool isLeft(const Vec2 &normal) const;

    bool isUpLeftCurve(const Vec2 &normal) const;

    bool isUp(const Vec2 &normal) const;

    bool isUpRightCurve(const Vec2 &normal) const;

private:
    Segment *path[4];
    float pointsOnPath[9];
    float right;
    float left;
    float down;
    float up;
    float pathLen;
    float distFromPath;
    float quartOfCircleLen;
    float distanceBetweenGlasses;
    float w;
    float h;
    int numOfGlasses;

    bool isZero(float value) const;
};

#endif //NATIVE_ACTIVITY_GLASSOBJECTSCONSTANTS_H
