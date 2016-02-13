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

        unsigned short indices[] = {0, 1, 1, 2, 2, 3, 4, 5, 5, 6, 6, 7};

        initialize(points, 8, indices, 12);
}
