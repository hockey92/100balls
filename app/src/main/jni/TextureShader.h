#ifndef NATIVE_ACTIVITY_TEXTURESHADER_H
#define NATIVE_ACTIVITY_TEXTURESHADER_H

#include "Shader.h"

class TextureShader : public Shader {
public:

protected:
    virtual const char *getVertexShaderSource();

    virtual const char *getFragmentShaderSource();

    virtual const char *getShaderName();
};

#endif //NATIVE_ACTIVITY_TEXTURESHADER_H
