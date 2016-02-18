#include "Segment.h"

Segment::Segment(Vec2 p1, Vec2 p2) : BaseShape() {
    init(p1, p2);
}

Segment::Segment(BaseShape *parent, Vec2 p1, Vec2 p2) : BaseShape() {
    init(p1, p2);
    this->parent = parent;
}

void Segment::init(Vec2 p1, Vec2 p2) {
    points[0] = initPoints[0] = p1;
    points[1] = initPoints[1] = p2;
}

Vec2 Segment::get(int i) const {
    return getCenter() + points[i];
}

void Segment::innerRotate(float angle) {
    this->angle += angle;
    points[0] = initPoints[0].rotate(this->angle);
    points[1] = initPoints[1].rotate(this->angle);
}
