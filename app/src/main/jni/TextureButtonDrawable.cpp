#include "TextureButtonDrawable.h"

#include "FileBuf.h"
#include "DrawUtils.h"

TextureButtonDrawable::TextureButtonDrawable() {
    texture = new Texture(new TGAImage(FileBuf::getInstance()->getPauseButton()));
}

void TextureButtonDrawable::draw(const DrawableData &drawableDate) {

    TextureShader *textureShader = drawableDate.textureShader;
    float *projMat = drawableDate.projMat;
    textureShader->beginRender(buttonVertex, 4, 6);
    textureShader->setMVP(projMat);
    textureShader->setTexture(texture);
    textureShader->setColor(color);

    GLushort indices[] = {0, 1, 2, 0, 2, 3};
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

unsigned int TextureButtonDrawable::type() {
    return 0;
}

bool TextureButtonDrawable::init() {
    buttonVertex->init();
    texture->init();
    return true;
}

void TextureButtonDrawable::afterButtonDataIsDefined() {
    float u, d, l, r;
    buttonData->aabb()->getCoords(l, r, u, d);

    float *coordsForTextureShader = DrawUtils::createCoordsForTextureShader(d, u, l, r, 0, 1, 0, 1);
    buttonVertex = new VertexBuff(coordsForTextureShader, 24);
    delete[] coordsForTextureShader;
}
