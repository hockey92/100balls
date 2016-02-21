#include "AABB.h"

AABB::AABB(Circle *circle) {
    right = up = circle->getR();
    left = down = -circle->getR();
}

AABB::AABB(Segment *segment) {

}

AABB::AABB(float left, float down, float right, float up) : left(left), down(down), right(right),
                                                            up(up) { }

AABB::AABB(const AABB &aabb, const Vec2 &moveVec) {
    right = fmaxf(aabb.right, aabb.right + moveVec.x());
    left = fmaxf(aabb.left, aabb.left + moveVec.x());
    up = fmaxf(aabb.up, aabb.up + moveVec.y());
    down = fmaxf(aabb.down, aabb.down + moveVec.y());
}

bool AABB::isIntersect(const AABB &a, const AABB &b) {
    return a.left > b.right || b.left > a.right || a.down > b.up || b.down > a.up;
}
