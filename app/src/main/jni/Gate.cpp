#include "Gate.h"
#include "Circle.h"

Gate::Gate() : BaseShape() {
    float points[] = {
            -0.12f, -1.15f,
            0.12f, -1.15f
    };
    childCount = 1;
    children = new BaseShape *[1];
    for (int i = 0; i < childCount; i++) {
        children[i > 3 ? i - 1 : i] = new Segment(
                this,
                Vec2(points[i * 2], points[i * 2 + 1]),
                Vec2(points[i * 2 + 2], points[i * 2 + 3])
        );
    }
}
