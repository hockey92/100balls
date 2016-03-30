#include "ButtonDrawable.h"

ButtonDrawable *ButtonDrawable::setColor(const Color &color) {
    this->color = color;
    return this;
}

void ButtonDrawable::setButtonData(ButtonData *buttonData) {
    this->buttonData = buttonData;
}
