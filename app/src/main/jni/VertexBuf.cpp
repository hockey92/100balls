#include "VertexBuf.h"

VertexBuf::VertexBuf(GLfloat *vertices, int size) {
    init(vertices, size);
}

void VertexBuf::bindBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuf::unbindBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuf::~VertexBuf() {
    glDeleteBuffers(1, &vbo);
}

VertexBuf::VertexBuf(const AABB &aabb) {
    float left;
    float right;
    float up;
    float down;
    aabb.getCoords(left, right, up, down);
    float indices[] = {
            right, up, 0.0f, 1.0f,
            left, up, 0.0f, 1.0f,
            left, down, 0.0f, 1.0f,
            right, down, 0.0f, 1.0f
    };
    init(indices, 16 * sizeof(float));
}

void VertexBuf::init(GLfloat *vertices, int size) {
    vbo = 0;

    glGenBuffers(1, &vbo);
    bindBuffer();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    unbindBuffer();
}
