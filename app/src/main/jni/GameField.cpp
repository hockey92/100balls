#include <vecmath.h>
#include "GameField.h"
#include "FileBuf.h"
#include "Context.h"
#include "ScoreService.h"
#include "TouchEventData.h"
#include "TextureButtonDrawable.h"

bool GameField::init() {

    if (Context::getInstance() == NULL) {
        return false;
    }

    font->init();

    ((GamePhysicsService *) Context::getInstance()->getPhysicsService())->init();

    return ScreenElement::init();
}

void GameField::draw(float *projMat, Shader *simpleShader, TextureShader *textureShader) {

    if (Context::getInstance() == NULL) {
        return;
    }

    ((GamePhysicsService *) Context::getInstance()->getPhysicsService())->nextFrame();

    font->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
    font->renderInteger(ScoreService::getInstance()->getTotal(), textureShader, projMat, 0, -0.6f);

    ((GamePhysicsService *) Context::getInstance()->getPhysicsService())->draw(
            DrawableData(simpleShader, textureShader, projMat));

    ScreenElement::draw(projMat, simpleShader, textureShader);
}

GameField::GameField() {
    font = new Font(new TGAImage(FileBuf::getInstance()->getFontImage()));

    float w = Context::getInstance()->getW();
    float h = Context::getInstance()->getH();

    Button *pauseButton = new Button(AABB(-0.1f, -0.1f, 0.1f, 0.1f), Vec2(w - 0.15f, h - 0.15f),
                                     (new TextureButtonDrawable())->setColor(
                                             Color(1.0f, 1.0f, 1.0f, 1.0f)),
                                     "gameFieldPauseButton");
    addScreenElement(pauseButton);
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
        case BUTTON_EVENT_DOWN:
            ((GamePhysicsService *) Context::getInstance()->getPhysicsService())->open();
            break;
        case BUTTON_EVENT_UP:
            ((GamePhysicsService *) Context::getInstance()->getPhysicsService())->close();
            break;
        default:
            break;
    }
    return true;
}
