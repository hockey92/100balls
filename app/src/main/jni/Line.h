#ifndef NATIVE_ACTIVITY_LINE_H
#define NATIVE_ACTIVITY_LINE_H

#include "Vec2.h"

class LineException {
};

class Line {
public:
    Line(const Vec2 &p1, const Vec2 &p2);

    float getValue(const Vec2 &p) const {
        return c[0] * p.x() + c[1] * p.y() + c[2];
    }

    Vec2 getNormal() const {
        return Vec2(c[0] * invSqrt, c[1] * invSqrt);
    }

    float getDistToPoint(const Vec2 &p) const {
        return getValue(p) * invSqrt;
    }

    static float getDet(const Line &l1, const Line &l2) {
        return l1.c[0] * l2.c[1] - l1.c[1] * l2.c[0];
    }

    static Vec2 getMutualPoint(const Line &l1, const Line &l2);

private:
    float c[3];//line coefficients
    float invSqrt;
};

#endif //NATIVE_ACTIVITY_LINE_H
