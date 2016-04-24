#include "ButtonDrawer.h"

ButtonDrawer *ButtonDrawer::setColor(const Color &color) {
    this->color = color;
    return this;
}

void ButtonDrawer::setButtonData(ButtonData *buttonData) {
    this->buttonData = buttonData;
}
