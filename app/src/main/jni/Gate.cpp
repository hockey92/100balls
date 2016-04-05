#include "Gate.h"
#include "Context.h"

Gate::Gate(float *vertices) {
    init(Vec2(vertices[10], vertices[11]), Vec2(vertices[16], vertices[17]));
}
