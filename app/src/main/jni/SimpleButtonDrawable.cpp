#include "SimpleButtonDrawable.h"
#include "FileBuf.h"

SimpleButtonDrawable::SimpleButtonDrawable() : fontColor(Color(1.0f, 1.0f, 1.0f, 1.0f)) {
    font = new Font(new TGAImage(FileBuf::getInstance()->getFontImage()));
}

void SimpleButtonDrawable::draw(const DrawableData &drawableDate) {

    Shader *simpleShader = drawableDate.simpleShader;
    TextureShader *textureShader = drawableDate.textureShader;
    float *projMat = drawableDate.projMat;
    simpleShader->beginRender(buttonVertex, 4, 4);
    simpleShader->setMVP(projMat);

    if (buttonData->pushed()) {
        GLushort indices1[] = {0, 1, 2, 0, 2, 3};
        simpleShader->setColor(color);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices1);
    }

    GLushort indices1[] = {0, 1, 1, 2, 2, 3, 3, 0};
    simpleShader->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
    glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, indices1);


    font->setColor(fontColor);
    font->renderText(buttonData->text(), textureShader, projMat, buttonData->aabb()->getCenter());
}

bool SimpleButtonDrawable::init() {
    buttonVertex->init();
    font->init();
    return true;
}

SimpleButtonDrawable *SimpleButtonDrawable::setFontColor(Color fontColor) {
    this->fontColor = fontColor;
    return this;
}

void SimpleButtonDrawable::afterButtonDataIsDefined() {
    buttonVertex = new VertexBuff(*(buttonData->aabb()), 0.0f);
}
