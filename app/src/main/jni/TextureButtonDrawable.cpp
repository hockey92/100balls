#include "TextureButtonDrawable.h"

#include "FileBuf.h"
#include "DrawUtils.h"

TextureButtonDrawable::TextureButtonDrawable() {

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
    float u, d, l, r;
    buttonData->aabb()->getCoords(l, r, u, d);

    float *vertices = DrawUtils::createCoordsForTextureShader(
            d, u, l, r, 0, 1, 0, 1
    );

    buttonVertex = new VertexBuff(vertices, 24 * sizeof(float));

    texture = new Texture(TGAImage(FileBuf::getInstance()->getPauseButton()));

    delete[] vertices;

    return true;
}
