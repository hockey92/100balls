#include "Container.h"
#include "Segment.h"

Container::Container() : SimpleShape() {
    float rawVertices[28];

    rawVertices[0] = -0.2f, rawVertices[1] = 0.5f;
    rawVertices[2] = -0.2f, rawVertices[3] = 1.0f;
    rawVertices[4] = -1.0f + 0.405f, rawVertices[5] = 1.0f;
    rawVertices[6] = -1.0f + 0.405f, rawVertices[7] = 0.25f;
    rawVertices[8] = -0.09f, rawVertices[9] = 0.05f;
    rawVertices[10] = -0.09f, rawVertices[11] = -0.13f;

    rawVertices[12] = -0.09f, rawVertices[13] = -0.22f;
    rawVertices[14] = 0.09f, rawVertices[15] = -0.22f;

    rawVertices[16] = 0.09f, rawVertices[17] = -0.13f;
    rawVertices[18] = 0.09f, rawVertices[19] = 0.05f;
    rawVertices[20] = 1.0f - 0.405f, rawVertices[21] = 0.25f;
    rawVertices[22] = 1.0f - 0.405f, rawVertices[23] = 1.0f;
    rawVertices[24] = 0.2f, rawVertices[25] = 1.0f;
    rawVertices[26] = 0.2f, rawVertices[27] = 0.5f;

    size_t size = 28;

    array.setValues(rawVertices, size);

    realChildCount = size / 2 - 4;
    children = new BaseShape *[realChildCount];
    int indices[] = {0, 1, 2, 3, 4, 6, 7, 9, 10, 11, 12, 13};
    for (int i = 0; i < realChildCount + 1; i++) {
        if (i == 5) {
            continue;
        }
        children[i > 5 ? i - 1 : i] = new Segment(
                this,
                Vec2(array.get(indices[i] * 2), array.get(indices[i] * 2 + 1)),
                Vec2(array.get(indices[i + 1] * 2), array.get(indices[i + 1] * 2 + 1))
        );
    }
}
