#include <vecmath.h>
#include "Menu.h"
#include "Context.h"

Menu::Menu() : slideX(0.0f) { }

void Menu::draw(float *projMat, Shader *simpleShader, TextureShader *textureShader) {

    slideX += slideDirection * 0.2f;

    if (slideX < -2.0f && slideDirection == -1.0f) {
        slideDirection = 0.0f;
    } else if (slideX > 0.0f && slideDirection == 1.0f) {
        slideX = 0.0f;
        slideDirection = 0.0f;
    }

    ndk_helper::Mat4 newProjMat =
            ndk_helper::Mat4(projMat) * ndk_helper::Mat4::Translation(slideX, 0.0f, 0.0f);

    simpleShader->beginRender(blackScreen, 4, 4);
    simpleShader->setColor(0.0f, 0.0f, 0.0f, 0.95f);
    simpleShader->setMVP(newProjMat.Ptr());
    GLushort indices[] = {0, 1, 2, 0, 2, 3};
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    simpleShader->endRender();

    ScreenElement::draw(newProjMat.Ptr(), simpleShader, textureShader);
}

bool Menu::doOperation(void *data) {
    return ScreenElement::doOperation(data);
}

float Menu::getSlide() const {
    return slideX;
}

void Menu::setSlide(float slideX) {
    this->slideX = slideX;
}

float Menu::getSliceDirection() const {
    return slideDirection;
}

void Menu::setSlideDirection(float sliceDirection) {
    this->slideDirection = sliceDirection;
}

bool Menu::init() {
    if (!ScreenElement::init()) {
        return false;
    }
    float w = Context::getInstance()->getW();
    float h = Context::getInstance()->getH();
    blackScreen = new VertexBuff(AABB(-w, -h, w, h), 0);
    return true;
}
