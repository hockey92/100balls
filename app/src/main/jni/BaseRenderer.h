#ifndef NATIVE_ACTIVITY_BASERENDERER_H
#define NATIVE_ACTIVITY_BASERENDERER_H

#include <GLES2/gl2.h>

class BaseRenderer {

public:
    BaseRenderer();
    virtual void draw(float* pm) = 0;

protected:
    GLuint program;

    static const char vertexShader[];
    static const char fragmentShader[];

    static GLuint createShader(GLenum shaderType, const char *src);
    static GLuint createProgram(const char *vtxSrc, const char *fragSrc);
};

#endif //NATIVE_ACTIVITY_BASERENDERER_H
