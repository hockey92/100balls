#include <vecmath.h>
#include "Menu.h"
#include "Context.h"
#include "SimpleButtonDrawable.h"

Menu::Menu() : slideX(0.0f), CallbackObject("Menu") {
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

void Menu::draw(float *projMat, Shader *simpleShader, TextureShader *textureShader) {

//    slideX += slideDirection * 0.2f;
//
//    if (slideX < -2.0f && slideDirection == -1.0f) {
//        slideDirection = 0.0f;
//    } else if (slideX > 0.0f && slideDirection == 1.0f) {
//        slideX = 0.0f;
//        slideDirection = 0.0f;
//    }

    slideX = 0;

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

//class StartButtonCommand : public Command {
//public:
//    StartButtonCommand(ScreenElement *screenManager) : screenManager(screenManager) { }
//
//    void *execute(void *data) {
////        screenManager->setCurrentScreen(1);
////        ((GamePhysicsService *) Context::getInstance()->getPhysicsService())->reset();
////        Context::getInstance()->getPhysicsService()->setStatus(PROCESSING);
//    }
//
//private:
//    ScreenElement *screenManager;
//};
//
//class PauseButtonCommand : public Command {
//public:
//    PauseButtonCommand(ScreenElement *screenManager) : screenManager(screenManager) { }
//
//    void *execute(void *data) {
////        screenManager->setCurrentScreen(0);
////        Context::getInstance()->getPhysicsService()->setStatus(PAUSED);
//    }
//
//private:
//    ScreenElement *screenManager;
//};
//
//class ContinueButtonCommand : public Command {
//public:
//    ContinueButtonCommand(ScreenElement *screenManager) : screenManager(screenManager) { }
//
//    void *execute(void *data) {
////        screenManager->setCurrentScreen(1);
////        Context::getInstance()->getPhysicsService()->setStatus(PROCESSING);
//    }
//
//private:
//    ScreenElement *screenManager;
//};

void Menu::beforeDraw() {
    if (Context::getInstance()->getPhysicsService()->getStatus() == STOPPED) {
        continueButton->setActive(false);
    } else {
        continueButton->setActive(true);
    }
}
