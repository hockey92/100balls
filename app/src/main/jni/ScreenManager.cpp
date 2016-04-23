#include <vecmath.h>
#include "ScreenManager.h"
#include "GameField.h"
#include "Menu.h"
#include "Context.h"

enum {
    SCREEN_MANAGER_MENU_SCREEN, SCREEN_MANAGER_GAME_SCREEN, SCREEN_MANAGER_GAME_OVER_SCREEN
};

ScreenManager::ScreenManager() : CallbackObject("screenManager") {

    addFunction("callbackPushPauseButton", ScreenManager::callbackPushPauseButton);
    addFunction("callbackPushContinueButton", ScreenManager::callbackPushContinueButton);
    addFunction("callbackPushStartButton", ScreenManager::callbackPushStartButton);

    Menu *menu = new Menu();
    GameField *gameField = new GameField();

    screens[SCREEN_MANAGER_MENU_SCREEN] = menu;
    screens[SCREEN_MANAGER_GAME_SCREEN] = gameField;

    setCurrentScreen(this, SCREEN_MANAGER_MENU_SCREEN);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawCurrentScreen(projMat);
}

bool ScreenManager::doOperation(void *data) {
    return screens[currentScreen]->doOperation(data);
}

void ScreenManager::setCurrentScreen(ScreenManager *screenManager, int currentScreen) {
    screenManager->currentScreen = currentScreen;
}

void ScreenManager::callbackPushPauseButton(CallbackObject *callbackObject, void *callbackData) {
    ScreenManager *screenManager = (ScreenManager *) callbackObject;
    Context::getInstance()->getPhysicsService()->setStatus(PAUSED);
    setCurrentScreen(screenManager, SCREEN_MANAGER_MENU_SCREEN);
}

void ScreenManager::callbackPushStartButton(CallbackObject *callbackObject, void *callbackData) {
    ScreenManager *screenManager = (ScreenManager *) callbackObject;
    setCurrentScreen(screenManager, SCREEN_MANAGER_GAME_SCREEN);
    ((GamePhysicsService*) Context::getInstance()->getPhysicsService())->reset();
    Context::getInstance()->getPhysicsService()->setStatus(PROCESSING);
}

void ScreenManager::callbackPushContinueButton(CallbackObject *callbackObject, void *callbackData) {
    ScreenManager *screenManager = (ScreenManager *) callbackObject;
    setCurrentScreen(screenManager, SCREEN_MANAGER_GAME_SCREEN);
    Context::getInstance()->getPhysicsService()->setStatus(PROCESSING);
}

void ScreenManager::drawCurrentScreen(float *projMat) {
    screens[currentScreen]->beforeDraw();
    screens[currentScreen]->draw(projMat, simpleShader, textureShader);
}
