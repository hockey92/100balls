#include <vecmath.h>
#include "ScreenManager.h"
#include "GameField.h"
#include "Menu.h"
#include "Context.h"
#include "SimpleButtonDrawable.h"
#include "TextureButtonDrawable.h"

class StartButtonCommand : public Command {
public:
    StartButtonCommand(ScreenManager *screenManager) : screenManager(screenManager) { }

    void *execute(void *data) { screenManager->setCurrentScreen(1); }

private:
    ScreenManager *screenManager;
};

class PauseButtonCommand : public Command {
public:
    PauseButtonCommand(ScreenManager *screenManager) : screenManager(screenManager) { }

    void *execute(void *data) { screenManager->setCurrentScreen(0); }

private:
    ScreenManager *screenManager;
};

ScreenManager::ScreenManager() {

    Menu *menu = new Menu();
    GameField *gameField = new GameField();

    AABB buttonAABB = AABB(-0.90f, -0.15f, 0.90f, 0.15f);
    Button *startButton = new Button(buttonAABB, Vec2(0, -0.5f),
                                     (new SimpleButtonDrawable())->setColor(
                                             Color(1.0f, 0.0f, 0.0f, 1.0f)));
    startButton->setText("NEW GAME");

    Button *exitButton = new Button(buttonAABB, Vec2(0, -0.9f), (new SimpleButtonDrawable())->setColor(
            Color(0.0f, 0.5f, 0.0f, 1.0f)));
    exitButton->setText("EXIT");

    float w = Context::getInstance()->getW();
    float h = Context::getInstance()->getH();

    Button *pauseButton = new Button(AABB(-0.1f, -0.1f, 0.1f, 0.1f), Vec2(w - 0.15f, h - 0.15f),
                                     (new TextureButtonDrawable())->setColor(
                                             Color(1.0f, 1.0f, 1.0f, 1.0f)));
    pauseButton->setCommand(new PauseButtonCommand(this));
    gameField->addScreenElement(pauseButton);

//    if (true) {
//        SimpleButtonDrawable* buttonDrawable = new SimpleButtonDrawable();
//        buttonDrawable->setColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
//        buttonDrawable->setFontColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
//        Button *tapToContinueButton = new Button(AABB(-w, -h, w, h), Vec2(0, 0), buttonDrawable);
//        tapToContinueButton->setText("TAP TO START");
//        gameField->addScreenElement(tapToContinueButton);
//    }

    startButton->setCommand(new StartButtonCommand(this));
    menu->addScreenElement(startButton);
    menu->addScreenElement(exitButton);

    screens.push_back(menu);
    screens.push_back(gameField);

    currentScreen = 0;
}

bool ScreenManager::init() {
    simpleShader = new Shader();
    simpleShader->compile();

    textureShader = new TextureShader();
    textureShader->compile();

    for (int i = 0; i < screens.size(); i++) {
        if (!screens[i]->init()) {
            return false;
        }
    }
    return true;
}

void ScreenManager::draw(float *projMat) {
//    screens[currentScreen]->draw(projMat);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    screens[1]->draw(projMat, simpleShader, textureShader);

    screens[0]->draw(projMat, simpleShader, textureShader);
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
