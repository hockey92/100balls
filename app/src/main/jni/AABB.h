#ifndef NATIVE_ACTIVITY_AABB_H
#define NATIVE_ACTIVITY_AABB_H

#include "Circle.h"

class AABB {
public:
    AABB(Circle *circle);

    AABB(Segment *segment);

    AABB(float left, float down, float right, float up);

    AABB(const AABB&aabb, const Vec2& moveVec);

    static bool isIntersect(const AABB& a, const AABB& b);

private:
    float left;
    float right;
    float up;
    float down;
};

#endif //NATIVE_ACTIVITY_AABB_H
