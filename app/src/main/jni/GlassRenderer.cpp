#include "GlassRenderer.h"

GlassRenderer::GlassRenderer() {

    vertices = new Vertex[4];
    vertices[0].pos[0] = -0.23f;
    vertices[0].pos[1] = 0.30f;
    vertices[0].pos[2] = 0.f;

    vertices[1].pos[0] = -0.15f;
    vertices[1].pos[1] = -0.30f;
    vertices[1].pos[2] = 0.f;

    vertices[2].pos[0] = 0.15f;
    vertices[2].pos[1] = -0.30f;
    vertices[2].pos[2] = 0.f;

    vertices[3].pos[0] = 0.23f;
    vertices[3].pos[1] = 0.30f;
    vertices[3].pos[2] = 0.f;

    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, vertices, GL_STATIC_DRAW);
}

void GlassRenderer::innerRender(float* pm) {
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glVertexAttribPointer(mPosAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (const GLvoid *) offsetof(Vertex, pos));
    glEnableVertexAttribArray(mPosAttrib);

    glUniformMatrix2fv(mScaleRotUniform, 1, GL_FALSE, mScaleRot);
    glUniformMatrix4fv(projection, 1, GL_FALSE, pm);
    glUniform2fv(mOffsetUniform, 1, mOffsets);

    short indices[] = {0, 1, 1, 2, 2, 3};

    glDrawElements(GL_LINES, 6, GL_UNSIGNED_SHORT, &indices[0]);
}
