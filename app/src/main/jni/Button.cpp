#include <vecmath.h>
#include "Button.h"
#include "TouchEventData.h"

Button::Button(const AABB &aabb, const Vec2 &center, ButtonDrawer *drawable, std::string buttonId) : drawable(drawable), buttonData(ButtonData(aabb, center)), CallbackObject(buttonId) {
    this->drawable = drawable;
    drawable->setButtonData(&buttonData);
}

bool Button::init() {
    return drawable->init();
}

void Button::draw(float *projMat, Shader *simpleShader, TextureShader *textureShader) {
    drawable->draw(DrawableData(simpleShader, textureShader, projMat));
}

bool Button::doOperation(void *data) {
    TouchEventData *eventData = (TouchEventData *) data;
    bool pushed = buttonData.pushed();
    AABB *aabb = buttonData.aabb();
    switch (eventData->type) {
        case BUTTON_EVENT_DOWN:
            if (!pushed) {
                if (aabb->isPointBelong(eventData->position)) {
                    buttonData.setPushed(true);
                    return true;
                }
            }
            break;
        case BUTTON_EVENT_UP:
            if (pushed) {
                buttonData.setPushed(false);
                if (aabb->isPointBelong(eventData->position)) {
                    callback(this);
                    return true;
                }
            }
            break;
        default:
            break;
    }
    return false;
}

Button::~Button() {
    if (drawable) {
        delete drawable;
    }
}

Button *Button::setText(const std::string &text) {
    buttonData.setText(text);
    return this;
}

