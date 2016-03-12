#include <vecmath.h>
#include "GameField.h"
#include "FileBuf.h"
#include "GameCoords.h"
#include "ScoreService.h"
#include "TouchEventData.h"

bool GameField::init() {

    if (GameCoords::getInstance() == NULL) {
        return false;
    }

    textureShader = new TextureShader();
    textureShader->compile();

    simpleShader = new Shader();
    simpleShader->compile();

    float *container = GameCoords::getInstance()->getCoords(CONTAINER)->createCoordsForShader(0.0f);
    float *glass = GameCoords::getInstance()->getCoords(GLASS)->createCoordsForShader(0.1f);
    float *vertices = GameCoords::getInstance()->getCoords(CIRCLE)->createCoordsForShader(0.0f);

    circleVertices = new VertexBuf(vertices, 24 * sizeof(float));
    containerVertices = new VertexBuf(container,
                                      GameCoords::getInstance()->getCoords(CONTAINER)->getSize() *
                                      4 * sizeof(float));
    glassVertices = new VertexBuf(glass, 16 * sizeof(float));

    TGAImage *image = new TGAImage(FileBuf::getInstance()->getCircle());

    texture = new Texture(*image);

    font->init();

    delete[] glass;
    delete[] vertices;
    delete[] container;

    return ScreenElement::init();
}

void GameField::doFrame(float *projMat) {

    if (physicsService == NULL && GameCoords::getInstance() != NULL) {
        physicsService = new PhysicsService();
    }

    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (physicsService == NULL) {
        return;
    }

    physicsService->nextFrame();

    physicsService->draw(projMat, simpleShader, containerVertices);

    simpleShader->beginRender(glassVertices, 4, 4);
    for (std::vector<PhysicsObject *>::iterator iter = physicsService->getObjects()->begin();
         iter != physicsService->getObjects()->end(); iter++) {
        (*iter)->draw(projMat, simpleShader);
    }
    simpleShader->endRender();

    textureShader->beginRender(circleVertices, 4, 6);
    textureShader->setTexture(texture);
    for (std::vector<PhysicsObject *>::iterator iter = physicsService->getObjects()->begin();
         iter != physicsService->getObjects()->end(); iter++) {
        if ((*iter)->isDeleted()) continue;
        BaseShape *shape = (*iter)->getShape();
        if (shape->type() == 1) {
            Vec2 center = shape->getCenter();
            textureShader->setMVP((ndk_helper::Mat4(projMat) *
                                   ndk_helper::Mat4::Translation(center.x(), center.y(),
                                                                 0.0f)).Ptr());
            textureShader->render();
        }
    }
    textureShader->endRender();

//    font->renderInteger(ScoreService::getInstance()->getTotal(), textureShader, projMat, 0, -0.6f);

    ScreenElement::doFrame(projMat);
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
