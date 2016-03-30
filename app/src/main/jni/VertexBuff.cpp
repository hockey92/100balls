#include "VertexBuff.h"

VertexBuff::VertexBuff(GLfloat *vertices, int size) {
    init(vertices, size);
}

void VertexBuff::bindBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuff::unbindBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuff::~VertexBuff() {
    glDeleteBuffers(1, &vbo);
}

VertexBuff::VertexBuff(const AABB &aabb, float z) {
    float left;
    float right;
    float up;
    float down;
    aabb.getCoords(left, right, up, down);
    float indices[] = {
            right, up, z, 1.0f,
            left, up, z, 1.0f,
            left, down, z, 1.0f,
            right, down, z, 1.0f
    };
    init(indices, 16 * sizeof(float));
}

void VertexBuff::init(GLfloat *vertices, int size) {
    vbo = 0;

    glGenBuffers(1, &vbo);
    bindBuffer();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    unbindBuffer();
}
