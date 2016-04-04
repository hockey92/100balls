#include "GlassShape.h"
#include "Segment.h"

GlassShape::GlassShape() : SimpleShape() {
    float vertices[8];

    float d = 0.2f;

    float left = -d * 0.8f;
    float down = -d;
    float right = d * 0.8f;
    float up = d;

    vertices[0] = left, vertices[1] = up;
    vertices[2] = 0.65f * left, vertices[3] = down;
    vertices[4] = 0.65f * right, vertices[5] = down;
    vertices[6] = right, vertices[7] = up;

    array.setValues(vertices, 8);

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
