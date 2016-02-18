#include "Gate.h"
#include "Circle.h"

Gate::Gate() {
    float points[] = {
            -0.12f, -1.15f,
            0.12f, -1.15f
    };
    init(Vec2(points[0], points[1]), Vec2(points[2], points[3]));
}
