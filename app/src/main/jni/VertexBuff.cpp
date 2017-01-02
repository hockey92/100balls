#include "VertexBuff.h"
#include <typeinfo>

VertexBuff::VertexBuff(GLfloat *vertices, int size) {
    arrayWrapper.setValues(vertices, size);
}

void VertexBuff::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuff::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuff::~VertexBuff() {
    kill();
}

VertexBuff::VertexBuff(const AABB &aabb, float z) {
    float left;
    float right;
    float up;
    float down;
    aabb.getCoords(left, right, up, down);
    float indices[] = {right, up, z, 1.0f,
                       left, up, z, 1.0f,
                       left, down, z, 1.0f,
                       right, down, z, 1.0f};
    arrayWrapper.setValues(indices, 16);
}

void VertexBuff::innerInit() {
    vbo = 0;

    glGenBuffers(1, &vbo);
    bind();
    glBufferData(GL_ARRAY_BUFFER, arrayWrapper.size() * sizeof(float),
                 arrayWrapper.ptr(), GL_STATIC_DRAW);
    unbind();
}

void VertexBuff::kill() {
    glDeleteBuffers(1, &vbo);
}

int VertexBuff::size() {
    return arrayWrapper.size();
}

bool VertexBuff::equals(const GLObject &b) const {
    try {
        const VertexBuff &that = dynamic_cast<const VertexBuff &>(b);
        if (arrayWrapper.size() != that.arrayWrapper.size()) {
            return false;
        }
        for (int i = 0; i < arrayWrapper.size(); i++) {
            if (arrayWrapper.get(i) != that.arrayWrapper.get(i)) {
                return false;
            }
        }
    } catch (const std::bad_cast &e) {
        return false;
    }
    return true;
}

float VertexBuff::get(int i) {
    return arrayWrapper.get(i);
}
