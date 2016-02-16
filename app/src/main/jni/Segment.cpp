#include "Segment.h"

Segment::Segment(Vec2 p1, Vec2 p2) : BaseShape() {
    points[0] = initPoints[0] = p1;
    points[1] = initPoints[1] = p2;
}

Segment::Segment(BaseShape *parent, Vec2 p1, Vec2 p2) : BaseShape() {
    points[0] = initPoints[0] = p1;
    points[1] = initPoints[1] = p2;

    this->parent = parent;
}

void Segment::innerRotate(float angle) {

}
