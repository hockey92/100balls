#include "ChainRenderer.h"

ChainRenderer::ChainRenderer(float *points, int num) {
    initialize(points, num);
}

void ChainRenderer::innerRender(float *pm) {
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glVertexAttribPointer(mPosAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (const GLvoid *) offsetof(Vertex, pos));
    glEnableVertexAttribArray(mPosAttrib);

    glUniformMatrix2fv(mScaleRotUniform, 1, GL_FALSE, mScaleRot);
    glUniformMatrix4fv(projection, 1, GL_FALSE, pm);
    glUniform2fv(mOffsetUniform, 1, mOffsets);

    glDrawElements(GL_LINES, (num - 1) * 2, GL_UNSIGNED_SHORT, indices);
}

void ChainRenderer::initialize(float *points, int num) {
    this->num = num;

    vertices = new Vertex[num];
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < 3; j++) {
            vertices[i].pos[j] = points[i * 3 + j];
        }
    }

    indices = new unsigned short[(num - 1) * 2];
    for (int i = 0; i < num - 1; i++) {
        indices[i * 2] = i;
        indices[i * 2 + 1] = i + 1;
    }

    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, num * sizeof(Vertex), vertices, GL_STATIC_DRAW);
}
