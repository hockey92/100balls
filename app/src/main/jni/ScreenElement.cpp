#include "ScreenElement.h"

void ScreenElement::addScreenElement(ScreenElement *screenElement) {
    screenElements.push_back(screenElement);
}

bool ScreenElement::doOperation(void *data) {
    bool operationIsApplied = false;
    for (int i = 0; i < screenElements.size(); i++) {
        if (screenElements[i]->doOperation(data)) {
            operationIsApplied = true;
        }
    }
    return operationIsApplied;
}

bool ScreenElement::init() {
    for (int i = 0; i < screenElements.size(); i++) {
        if (!screenElements[i]->init()) {
            return false;
        }
    }
    return true;
}

void ScreenElement::doFrame(float *projMat, Shader *simpleShader, TextureShader *textureShader) {
    for (int i = 0; i < screenElements.size(); i++) {
        screenElements[i]->doFrame(projMat, simpleShader, textureShader);
    }
}

void ScreenElement::doFrame(float *projMat) {

}
