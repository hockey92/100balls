#include <vecmath.h>
#include "GameField.h"
#include "FileBuf.h"
#include "Context.h"
#include "ScoreService.h"
#include "TouchEventData.h"

bool GameField::init() {

    if (Context::getInstance() == NULL) {
        return false;
    }

    font->init();

    ((PhysicsService *) Context::getInstance()->getPhysicsService())->init();

    return ScreenElement::init();
}

void GameField::draw(float *projMat, Shader *simpleShader, TextureShader *textureShader) {

    if (Context::getInstance() == NULL) {
        return;
    }

    ((PhysicsService *) Context::getInstance()->getPhysicsService())->nextFrame();

    font->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
    font->renderInteger(ScoreService::getInstance()->getTotal(), textureShader, projMat, 0, -0.6f);

    ((PhysicsService *) Context::getInstance()->getPhysicsService())->draw(
            DrawableData(simpleShader, textureShader, projMat));

    ScreenElement::draw(projMat, simpleShader, textureShader);
}

GameField::GameField() {
    font = new Font(new TGAImage(FileBuf::getInstance()->getFontImage()));
}

GameField::~GameField() {
    if (font) {
        delete font;
    }
}

bool GameField::doOperation(void *data) {
    if (ScreenElement::doOperation(data)) {
        return true;
    }

    if (Context::getInstance() == NULL) {
        return false;
    }

    TouchEventData *eventData = (TouchEventData *) data;
    switch (eventData->type) {
        case EVENT_DOWN:
            ((PhysicsService*) Context::getInstance()->getPhysicsService())->open();
            break;
        case EVENT_UP:
            ((PhysicsService*) Context::getInstance()->getPhysicsService())->close();
            break;
        default:
            break;
    }
    return true;
}
