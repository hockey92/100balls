#include "Menu.h"

Menu::Menu() {
//    buttons.push_back(new Button(AABB(-0.96f, -0.96f, -0.02f, -0.02f), Vec2(0, -0.5f)));
//    buttons.back()->setText("ZERO");
//    buttons.push_back(new Button(AABB(0.02f, -0.96f, 0.96f, -0.02f), Vec2(0, -0.5f)));
//    buttons.back()->setText("ONE");
//    buttons.push_back(new Button(AABB(-0.96f, 0.02f, -0.02f, 0.96f), Vec2(0, -0.5f)));
//    buttons.back()->setText("TWO");
//    buttons.push_back(new Button(AABB(0.02f, 0.02f, 0.96f, 0.96f), Vec2(0, -0.5f)));
//    buttons.back()->setText("THREE");
}

void Menu::doFrame(float *projMat) {
    glClearColor(0.9, 0.9, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ScreenElement::doFrame(projMat);
}

bool Menu::doOperation(void *data) {
    return ScreenElement::doOperation(data);
}

