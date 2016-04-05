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

//    float *container = GameCoords::getInstance()->getCoords(CONTAINER)->createCoordsForShader(0.0f);
//    float *glass = GameCoords::getInstance()->getCoords(GLASS)->createCoordsForShader(0.1f);
//    float *vertices = GameCoords::getInstance()->getCoords(CIRCLE)->createCoordsForShader(0.0f);
//
//    circleVertices = new VertexBuff(vertices, 24 * sizeof(float));
//    containerVertices = new VertexBuff(container,
//                                      GameCoords::getInstance()->getCoords(CONTAINER)->getSize() *
//                                      4 * sizeof(float));
//    glassVertices = new VertexBuff(glass, 16 * sizeof(float));
//
//    TGAImage *image = new TGAImage(FileBuf::getInstance()->getCircle());
//
//    texture = new Texture(*image);
//
    font->init();
//
//    delete[] glass;
//    delete[] vertices;
//    delete[] container;

    if (physicsService == NULL && Context::getInstance() != NULL) {
        physicsService = new PhysicsService(0, 0);
    }

    if (physicsService == NULL) {
        return false;
    }

    physicsService->init();

    return ScreenElement::init();
}

void GameField::draw(float *projMat, Shader *simpleShader, TextureShader *textureShader) {

    if (physicsService == NULL) {
        return;
    }

    physicsService->nextFrame();

    font->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
    font->renderInteger(ScoreService::getInstance()->getTotal(), textureShader, projMat, 0, -0.6f);

    physicsService->draw(DrawableData(simpleShader, textureShader, projMat));

//    physicsService->draw(projMat, simpleShader, containerVertices);
//
//    textureShader->beginRender(circleVertices, 4, 6);
//    textureShader->setTexture(texture);
//    for (std::vector<PhysicsObject *>::iterator iter = physicsService->getObjects()->begin();
//         iter != physicsService->getObjects()->end(); iter++) {
//        if ((*iter)->isDeleted()) continue;
//        BaseShape *shape = (*iter)->getShape();
//        if (shape->type() == 1) {
//            Vec2 center = shape->getCenter();
//            textureShader->setMVP((ndk_helper::Mat4(projMat) *
//                                   ndk_helper::Mat4::Translation(center.x(), center.y(),
//                                                                 0.0f)).Ptr());
//            textureShader->render();
//        }
//    }
//    textureShader->endRender();
//
//    simpleShader->beginRender(glassVertices, 4, 4);
//    for (std::vector<PhysicsObject *>::iterator iter = physicsService->getObjects()->begin();
//         iter != physicsService->getObjects()->end(); iter++) {
//        (*iter)->draw(projMat, simpleShader);
//    }
//    simpleShader->endRender();
//

    ScreenElement::draw(projMat, simpleShader, textureShader);
}

GameField::GameField() : physicsService(NULL) {
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

    if (physicsService == NULL) {
        return false;
    }

    TouchEventData *eventData = (TouchEventData *) data;
    switch (eventData->type) {
        case EVENT_DOWN:
            physicsService->open();
            break;
        case EVENT_UP:
            physicsService->close();
            break;
        default:
            break;
    }
    return true;
}
