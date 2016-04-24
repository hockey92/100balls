#include <vecmath.h>
#include "MenuScreen.h"
#include "Context.h"
#include "SimpleButtonDrawable.h"

MenuScreen::MenuScreen() : slideX(0.0f), CallbackObject("MenuScreen") {
    AABB buttonAABB = AABB(-0.90f, -0.15f, 0.90f, 0.15f);
    Button *startButton = new Button(buttonAABB, Vec2(0, -0.5f),
                                     (new SimpleButtonDrawable())->setColor(
                                             Color(1.0f, 0.0f, 0.0f, 1.0f)), "menuStartButton");
    startButton->setText("NEW GAME");

    Button *exitButton = new Button(buttonAABB, Vec2(0, -0.9f),
                                    (new SimpleButtonDrawable())->setColor(
                                            Color(0.0f, 0.5f, 0.0f, 1.0f)), "menuExitButton");
    exitButton->setText("EXIT");

    continueButton = new Button(buttonAABB, Vec2(0, -0.1f),
                                (new SimpleButtonDrawable())->setColor(
                                        Color(0.0f, 0.0f, 0.5f, 1.0f)), "menuContinueButton");
    continueButton->setText("CONTINUE");

    addScreenElement(startButton);
    addScreenElement(exitButton);
    addScreenElement(continueButton);
}

void MenuScreen::draw(float *projMat, Shader *simpleShader, TextureShader *textureShader) {

//    slideX += slideDirection * 0.2f;
//
//    if (slideX < -2.0f && slideDirection == -1.0f) {
//        slideDirection = 0.0f;
//    } else if (slideX > 0.0f && slideDirection == 1.0f) {
//        slideX = 0.0f;
//        slideDirection = 0.0f;
//    }
//
    slideX = 0;

    ndk_helper::Mat4 newProjMat =
            ndk_helper::Mat4(projMat) * ndk_helper::Mat4::Translation(slideX, 0.0f, 0.0f);
//
//    simpleShader->beginRender(blackScreen, 4, 4);
//    simpleShader->setColor(0.0f, 0.0f, 0.0f, 0.95f);
//    simpleShader->setMVP(newProjMat.Ptr());
//    GLushort indices[] = {0, 1, 2, 0, 2, 3};
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
//    simpleShader->endRender();

    ScreenElement::draw(newProjMat.Ptr(), simpleShader, textureShader);
}

bool MenuScreen::doOperation(void *data) {
    return ScreenElement::doOperation(data);
}

float MenuScreen::getSlide() const {
    return slideX;
}

void MenuScreen::setSlide(float slideX) {
    this->slideX = slideX;
}

float MenuScreen::getSliceDirection() const {
    return slideDirection;
}

void MenuScreen::setSlideDirection(float sliceDirection) {
    this->slideDirection = sliceDirection;
}

bool MenuScreen::init() {
    if (!ScreenElement::init()) {
        return false;
    }
    float w = Context::getInstance()->getW();
    float h = Context::getInstance()->getH();
    blackScreen = new VertexBuff(AABB(-w, -h, w, h), 0);
    return true;
}

void MenuScreen::beforeDraw() {
    if (Context::getInstance()->getPhysicsService()->getStatus() == STOPPED) {
        continueButton->setActive(false);
    } else {
        continueButton->setActive(true);
    }
}
