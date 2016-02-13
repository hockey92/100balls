#include "Segment.h"

Segment::Segment(Vec2 p1, Vec2 p2) : BaseShape(NULL) {
    points[0] = p1;
    points[1] = p2;

    _type = 2;
}

Segment::Segment(BaseShape *parent, Vec2 p1, Vec2 p2) : BaseShape(NULL) {
    points[0] = p1;
    points[1] = p2;

    _type = 2;

    this->parent = parent;
}
