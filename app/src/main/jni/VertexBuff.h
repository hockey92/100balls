#ifndef NATIVE_ACTIVITY_VERTEXBUFF_H
#define NATIVE_ACTIVITY_VERTEXBUFF_H

#include <GLES2/gl2.h>
#include "AABB.h"

class VertexBuff {
public:
    VertexBuff(GLfloat *vertices, int size);
    VertexBuff(const AABB &aabb, float z);
    ~VertexBuff();

    void bindBuffer();
    void unbindBuffer();
private:
    GLuint vbo;

    void init(GLfloat *vertices, int size);
};

#endif //NATIVE_ACTIVITY_VERTEXBUFF_H