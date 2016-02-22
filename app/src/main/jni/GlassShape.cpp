#include "GlassShape.h"
#include "Segment.h"

GlassShape::GlassShape() : BaseShape() {

    float left = -0.23f;
    float down = -0.3f;

    float right = 0.23f;
    float up = 0.3f;

    float points[] = {
            left, up,
            0.65f * left, down,
            0.65f * right, down,
            right, up
    };

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
