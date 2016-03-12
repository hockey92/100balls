#ifndef NATIVE_ACTIVITY_TEXTURESHADER_H
#define NATIVE_ACTIVITY_TEXTURESHADER_H

#include "Shader.h"
#include "Texture.h"

class TextureShader : public Shader {
public:
    virtual void compile();
    void setTexture(Texture *texture);
    virtual void beginRender(VertexBuf *vbuf, int size, int stride);
    virtual void render();

protected:
    int texCoordAttributeHandle;
    int samplerHandle;

    virtual const char *getVertexShaderSource();

    virtual const char *getFragmentShaderSource();

    virtual const char *getShaderName();
};

#endif //NATIVE_ACTIVITY_TEXTURESHADER_H
