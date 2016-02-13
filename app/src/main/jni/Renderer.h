#ifndef NATIVE_ACTIVITY_RENDERER_H
#define NATIVE_ACTIVITY_RENDERER_H

#include <GLES2/gl2.h>

struct Vertex {
    float pos[3];
};

class Renderer {

public:
    Renderer() : program(0) {}
    virtual void render(float* pm);

protected:
    GLuint vb;
    GLint mPosAttrib;
    GLint mScaleRotUniform;
    GLint mOffsetUniform;
    GLint projection;
    GLint mColorAttrib;

    float mOffsets[2];
    float mScaleRot[4];

    virtual void innerRender(float* pm) {}

protected:
    /*static*/ GLuint program;
//    static char VERTEX_SHADER[];
//    static char FRAGMENT_SHADER[];

    static GLuint createShader(GLenum shaderType, const char *src);
    static GLuint createProgram(const char *vtxSrc, const char *fragSrc);
};

#endif //NATIVE_ACTIVITY_RENDERER_H
