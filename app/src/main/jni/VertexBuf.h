#ifndef NATIVE_ACTIVITY_VERTEXBUFF_H
#define NATIVE_ACTIVITY_VERTEXBUFF_H

#include <GLES2/gl2.h>

class VertexBuf {
public:
    VertexBuf(GLfloat *vertices, int size);
    ~VertexBuf();

    void bindBuffer();
    void unbindBuffer();
private:
    GLuint vbo;
};

#endif //NATIVE_ACTIVITY_VERTEXBUFF_H
