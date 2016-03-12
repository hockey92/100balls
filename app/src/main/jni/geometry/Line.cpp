#include <math.h>
#include "Line.h"
#include "common.hpp"

Line::Line(const Vec2 &p1, const Vec2 &p2) {
    c[0] = p1.y() - p2.y();
    c[1] = p2.x() - p1.x();
    c[2] = p1.x() * p2.y() - p1.y() * p2.x();
    invSqrt = 1.f / sqrtf(c[0] * c[0] + c[1] * c[1]);
}

Vec2 Line::getMutualPoint(const Line &l1, const Line &l2) {
    float d = getDet(l1, l2);
    ASSERT(d != 0)
    float d1 = -l1.c[2] * l2.c[1] + l1.c[1] * l2.c[2];
    float d2 = -l1.c[0] * l2.c[2] + l1.c[2] * l2.c[0];
    return Vec2(d1 / d, d2 / d);
}
