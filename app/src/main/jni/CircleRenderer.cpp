#include "CircleRenderer.h"

CircleRenderer::CircleRenderer() : ChainRenderer() {
    float r = 0.06;
    float points[] = {
            r, r, 0.0f,
            r, -r, 0.0f,
            -r, -r, 0.0f,
            -r, r, 0.0f,
            r, r, 0.0f
    };
    initialize(points, 5);
}
