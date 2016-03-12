#include "ScreenManager.h"
#include "GameField.h"
#include "Menu.h"

class StartButtonCommand : public Command {
public:
    StartButtonCommand(ScreenManager *screenManager) : screenManager(screenManager) { }

    void *execute(void *data) { screenManager->currentScreen = 1; }

private:
    ScreenManager *screenManager;
};

class PauseButtonCommand : public Command {
public:
    PauseButtonCommand(ScreenManager *screenManager) : screenManager(screenManager) { }

    void *execute(void *data) { screenManager->currentScreen = 0; }

private:
    ScreenManager *screenManager;
};

ScreenManager::ScreenManager() {

    Menu *menu = new Menu();
    GameField *gameField = new GameField();

    Button *startButton = new Button(AABB(-0.96f, -0.96f, -0.02f, -0.02f), Vec2(0, -0.5f));
    startButton->setText("START");

    Button *pauseButton = new Button(AABB(-0.1f, -0.1f, 0.1f, 0.1f), Vec2(0, 0.8f));
    pauseButton->setCommand(new PauseButtonCommand(this));
    gameField->addScreenElement(pauseButton);

    startButton->setCommand(new StartButtonCommand(this));
    menu->addScreenElement(startButton);

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
    screens[currentScreen]->doFrame(projMat);
}

bool ScreenManager::doOperation(void *data) {
    return screens[currentScreen]->doOperation(data);
}
