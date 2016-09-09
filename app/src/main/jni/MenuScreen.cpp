#include <vecmath.h>
#include "MenuScreen.h"
#include "Context.h"
#include "SimpleButtonDrawable.h"

MenuScreen::MenuScreen() : CallbackObject("MenuScreen") {
    AABB buttonAABB = AABB(-0.90f, -0.15f, 0.90f, 0.15f);
    Button *startButton = new Button(buttonAABB, Vec2(0, -0.5f), (new SimpleButtonDrawable())->setColor(Color(1.0f, 0.0f, 0.0f, 1.0f)), "menuStartButton");
    startButton->setText("NEW GAME");

    Button *exitButton = new Button(buttonAABB, Vec2(0, -0.9f), (new SimpleButtonDrawable())->setColor(Color(0.0f, 0.5f, 0.0f, 1.0f)), "menuExitButton");
    exitButton->setText("EXIT");

    continueButton = new Button(buttonAABB, Vec2(0, -0.1f), (new SimpleButtonDrawable())->setColor(Color(0.0f, 0.0f, 0.5f, 1.0f)), "menuContinueButton");
    continueButton->setText("CONTINUE");

    addScreenElement(startButton);
    addScreenElement(exitButton);
    addScreenElement(continueButton);
}

bool MenuScreen::doOperation(void *data) {
    return ScreenElement::doOperation(data);
}

void MenuScreen::beforeDraw() {
    if (Context::getInstance()->getPhysicsService()->getStatus() == STOPPED) {
        continueButton->setActive(false);
    } else {
        continueButton->setActive(true);
    }
}
