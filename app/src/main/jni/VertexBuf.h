#ifndef NATIVE_ACTIVITY_VERTEXBUFF_H
#define NATIVE_ACTIVITY_VERTEXBUFF_H

#include <GLES2/gl2.h>
#include "AABB.h"

class VertexBuf {
public:
    VertexBuf(GLfloat *vertices, int size);
    VertexBuf(const AABB &aabb, float z);
    ~VertexBuf();

    void bindBuffer();
    void unbindBuffer();
private:
    GLuint vbo;

    void init(GLfloat *vertices, int size);
};

#endif //NATIVE_ACTIVITY_VERTEXBUFF_H
