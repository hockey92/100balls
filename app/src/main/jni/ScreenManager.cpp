#include <vecmath.h>
#include "ScreenManager.h"
#include "GameField.h"
#include "Menu.h"

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

    AABB buttonAABB = AABB(-0.96f, -0.15f, 0.96f, 0.15f);
    Button *startButton = new Button(buttonAABB, Vec2(0, -0.5f));
//    startButton->setText("NEW GAME");

    Button *exitButton = new Button(buttonAABB, Vec2(0, -0.9f));
//    exitButton->setText("EXIT");

    Button *pauseButton = new Button(AABB(-0.1f, -0.1f, 0.1f, 0.1f), Vec2(0, 0.8f));
    pauseButton->setCommand(new PauseButtonCommand(this));
    gameField->addScreenElement(pauseButton);

    startButton->setCommand(new StartButtonCommand(this));
    menu->addScreenElement(startButton);
    menu->addScreenElement(exitButton);

    screens.push_back(menu);
    screens.push_back(gameField);

    currentScreen = 0;
}

bool ScreenManager::init() {

    for (int i = 0; i < screens.size(); i++) {
        if (!screens[i]->init()) {
            return false;
        }
    }
    return true;
}

void ScreenManager::doFrame(float *projMat) {
//    screens[currentScreen]->doFrame(projMat);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    screens[1]->doFrame(projMat);

    screens[0]->doFrame(projMat);
}

bool ScreenManager::doOperation(void *data) {
    return screens[currentScreen]->doOperation(data);
}

void ScreenManager::setCurrentScreen(int currentScreen) {
    Menu *menu = (Menu *) screens[0];
    if (currentScreen == 1) {
        menu->setSlideDirection(1.0f);
    } else if (currentScreen == 0) {
        menu->setSlideDirection(-1.0f);
    }

    this->currentScreen = currentScreen;
}
