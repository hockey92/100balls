#ifndef NATIVE_ACTIVITY_GAMEFIELD_H
#define NATIVE_ACTIVITY_GAMEFIELD_H

#include "TextureShader.h"
#include "VertexBuf.h"
#include "Texture.h"

class GameField {

public:
    void init();
    void doFrame();

private:
    TextureShader* textureShader;
    VertexBuf* vertexBuf;
    Texture* texture;
};

#endif //NATIVE_ACTIVITY_GAMEFIELD_H
