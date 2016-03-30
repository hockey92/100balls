#include "GlassShape.h"
#include "Segment.h"
#include "GameCoords.h"

GlassShape::GlassShape() : BaseShape() {

    float *vertices = GameCoords::getInstance()->getCoords(GLASS)->getData();

    realChildCount = 3;
    children = new BaseShape *[3];
    for (int i = 0; i < realChildCount; i++) {
        children[i] = new Segment(
                this,
                Vec2(vertices[i * 2], vertices[i * 2 + 1]),
                Vec2(vertices[i * 2 + 2], vertices[i * 2 + 3])
        );
    }
}

unsigned int GlassShape::type() const {
    return 10;
}
