#ifndef NATIVE_ACTIVITY_VERTEXBUFF_H
#define NATIVE_ACTIVITY_VERTEXBUFF_H

#include <GLES2/gl2.h>
#include "AABB.h"
#include "Array.h"
#include "GLObject.h"

class VertexBuff : public GLObject {
public:
    VertexBuff(GLfloat *vertices, int size);

    VertexBuff(const AABB &aabb, float z);

    virtual ~VertexBuff();

    void kill();

    void bind();

    void unbind();

    int size();

    float get(int i);

    virtual bool equals(const GLObject &b) const;

protected:
    virtual void innerInit();

private:
    GLuint vbo;

    Array arrayWrapper;
};

#endif //NATIVE_ACTIVITY_VERTEXBUFF_H
