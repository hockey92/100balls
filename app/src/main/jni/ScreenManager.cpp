#include <vecmath.h>
#include "ScreenManager.h"
#include "GameField.h"
#include "Menu.h"
#include "Context.h"

enum {
    SCREEN_MANAGER_MENU, SCREEN_MANAGER_GAME_FIELD
};

ScreenManager::ScreenManager() : CallbackObject("screenManager") {

    addFunction("callbackPushPauseButton", ScreenManager::callbackPushPauseButton);
    addFunction("callbackPushContinueButton", ScreenManager::callbackPushContinueButton);
    addFunction("callbackPushStartButton", ScreenManager::callbackPushStartButton);

    Menu *menu = new Menu();
    GameField *gameField = new GameField();

    screens[SCREEN_MANAGER_MENU] = menu;
    screens[SCREEN_MANAGER_GAME_FIELD] = gameField;

    currentScreen = SCREEN_MANAGER_MENU;
}

bool ScreenManager::init() {
    simpleShader = new Shader();
    simpleShader->compile();

    textureShader = new TextureShader();
    textureShader->compile();

    for (int i = 0; i < 2; i++) {
        if (!screens[i]->init()) {
            return false;
        }
    }
    return true;
}

void ScreenManager::draw(float *projMat) {
//    screens[currentScreen]->draw(projMat);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    screens[currentScreen]->draw(projMat, simpleShader, textureShader);

//    screens[1]->draw(projMat, simpleShader, textureShader);
//
//    screens[0]->draw(projMat, simpleShader, textureShader);
}

bool ScreenManager::doOperation(void *data) {
    return screens[currentScreen]->doOperation(data);
}

void ScreenManager::setCurrentScreen(int currentScreen) {
    Menu *menu = (Menu *) screens[0];
    if (currentScreen == 1) {
        menu->setSlideDirection(-1.0f);
    } else if (currentScreen == 0) {
        menu->setSlideDirection(1.0f);
    }
    this->currentScreen = currentScreen;
}

void ScreenManager::callbackPushPauseButton(CallbackObject *callbackObject, void *callbackData) {
    int i = 0;
}

void ScreenManager::callbackPushStartButton(CallbackObject *callbackObject, void *callbackData) {
    ScreenManager* screenManager = (ScreenManager*) callbackObject;
    screenManager->currentScreen = SCREEN_MANAGER_GAME_FIELD;
    Context::getInstance()->getPhysicsService()->setStatus(PROCESSING);
}

void ScreenManager::callbackPushContinueButton(CallbackObject *callbackObject, void *callbackData) {
    int i = 0;
}
