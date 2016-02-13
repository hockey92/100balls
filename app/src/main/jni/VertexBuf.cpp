#include "VertexBuf.h"

VertexBuf::VertexBuf(GLfloat *vertices, int size) {
    vbo = 0;

    glGenBuffers(1, &vbo);
    bindBuffer();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    unbindBuffer();
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
