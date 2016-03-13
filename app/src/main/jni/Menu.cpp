#include <vecmath.h>
#include "Menu.h"

Menu::Menu() : slideX(0.0f) {
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
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    slideX += slideDirection * 0.05f;

    if (slideX > 2.0f && slideDirection == 1.0f) {
        slideDirection = 0.0f;
    } else if (slideX < 0.0f && slideDirection == -1.0f) {
        slideX = 0.0f;
        slideDirection = 0.0f;
    }

    projMat = (ndk_helper::Mat4(projMat) *
               ndk_helper::Mat4::Translation(slideX, 0.0f, 0.0f)).Ptr();
    ScreenElement::doFrame(projMat);
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
