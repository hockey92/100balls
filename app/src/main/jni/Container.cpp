#include "Container.h"
#include "Segment.h"

Container::Container() : BaseShape(RendererPool::getInstance()->getRenderer("container")) {
    float points[] = {
            -1.50f, 0.80f,
            -1.50f, -0.20f,
            -0.12f, -0.90f,
            -0.12f, -1.15f,
            0.12f, -1.15f,
            0.12f, -0.90f,
            1.50f, -0.20f,
            1.50f, 0.80f
    };
    childCount = 8;
    children = new BaseShape *[8];
    for (int i = 0; i < childCount; i++) {
        children[i] = new Segment(
                Vec2(points[i * 2], points[i * 2 + 1]),
                Vec2(points[i * 2 + 2], points[i * 2 + 3])
        );
    }
}
