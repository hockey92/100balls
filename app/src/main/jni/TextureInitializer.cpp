#include "TextureInitializer.h"
#include "FileBuf.h"
#include "DrawUtils.h"

TextureInitializer::TextureInitializer() {
    texture = new Texture(new TGAImage(FileBuf::getInstance()->getCircle()));
    float zCoord = 0.0f;
    float r = 0.0355f;

    float *result = DrawUtils::createCoordsForTextureShader(-r, r, -r, r, 0.0f, 1.0f, 0.0f, 1.0f);
    vertexBuff = new VertexBuff(result, 24);
    delete[] result;
}


bool TextureInitializer::init() {
    vertexBuff->init();
    texture->init();
    return true;
}

TextureInitializer::~TextureInitializer() { }

void TextureInitializer::startRender(Shader *simpleShader, TextureShader *textureShader) {
    textureShader->beginRender(vertexBuff, 4, 6);
    textureShader->setTexture(texture);
}
