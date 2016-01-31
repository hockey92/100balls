#include "ContainerRenderer.h"

ContainerRenderer::ContainerRenderer() {
        float points[] = {
                -1.50f, 0.80f, 0.0f,
                -1.50f, -0.20f, 0.0f,
                -0.12f, -0.90f, 0.0f,
                -0.12f, -1.15f, 0.0f,
                0.12f, -1.15f, 0.0f,
                0.12f, -0.90f, 0.0f,
                1.50f, -0.20f, 0.0f,
                1.50f, 0.80f, 0.0f
        };
        initialize(points, 8);
}
