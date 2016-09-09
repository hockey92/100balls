#ifndef NATIVE_ACTIVITY_CIRCLEINITIALIZER_H
#define NATIVE_ACTIVITY_CIRCLEINITIALIZER_H

#include "Initializer.h"

class TextureInitializer : public Initializer {
public:
    TextureInitializer();

    virtual ~TextureInitializer();

    void startRender(Shader *simpleShader, TextureShader *textureShader);

    bool init();

private:
    VertexBuff *vertexBuff;
    Texture *texture;
    TGAImage *image;
};

#endif //NATIVE_ACTIVITY_CIRCLEINITIALIZER_H
