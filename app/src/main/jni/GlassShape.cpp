#include "GlassShape.h"
#include "Segment.h"
#include "GameCoords.h"

GlassShape::GlassShape() : BaseShape() {

    float *points = GameCoords::getInstance()->getCoords(GLASS)->getData();

    realChildCount = 3;
    children = new BaseShape *[3];
    for (int i = 0; i < realChildCount; i++) {
        children[i] = new Segment(
                this,
                Vec2(points[i * 2], points[i * 2 + 1]),
                Vec2(points[i * 2 + 2], points[i * 2 + 3])
        );
    }
}
