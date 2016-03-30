#ifndef NATIVE_ACTIVITY_INITIALIZER_H
#define NATIVE_ACTIVITY_INITIALIZER_H

#include "Shader.h"
#include "TextureShader.h"

class Initializer {
public:
    virtual bool init() = 0;

    virtual void startRender(Shader *simpleShader, TextureShader *textureShader) = 0;

    virtual void endRender(Shader *simpleShader, TextureShader *textureShader);
};

#endif //NATIVE_ACTIVITY_DRAWABLE_H
