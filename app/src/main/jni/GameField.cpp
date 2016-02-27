#include <vecmath.h>
#include "GameField.h"
#include "FileBuf.h"
#include "GameCoords.h"

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
    float *vertices = GameCoords::getInstance()->getCoords(BALL)->createCoordsForShader(0.0f);

    circleVertices = new VertexBuf(vertices, 24 * sizeof(float));
    containerVertices = new VertexBuf(container, GameCoords::getInstance()->getCoords(CONTAINER)->getSize() * 4 * sizeof(float));
    glassVertices = new VertexBuf(glass, 16 * sizeof(float));
    texture = new Texture(FileBuf::getInstance()->getFile());

    delete[] glass;
    delete[] vertices;
    delete[] container;

    return true;
}

void GameField::doFrame(float *projMat) {

    if (physicsService == NULL && GameCoords::getInstance() != NULL) {
        physicsService = new PhysicsService();
    }

    glClearColor(0.5, 0.0, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (physicsService == NULL) {
        return;
    }

    physicsService->nextFrame();

    simpleShader->beginRender(containerVertices, 4, 4);
    textureShader->setMVP(ndk_helper::Mat4(projMat).Ptr());
    GLushort indices[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11};
    glDrawElements(GL_LINES, 22, GL_UNSIGNED_SHORT, indices);

    textureShader->beginRender(circleVertices, 4, 6);
    textureShader->setTexture(texture);

    for (std::vector<PhysicsObject *>::iterator iter = physicsService->getObjects()->begin();
         iter != physicsService->getObjects()->end(); iter++) {
        BaseShape *shape = (*iter)->getShape();
        if (shape->type() == 1) {
            Vec2 center = shape->getCenter();
            textureShader->setMVP((ndk_helper::Mat4(projMat) *
                                   ndk_helper::Mat4::Translation(center.x(), center.y(),
                                                                 0.0f)).Ptr());
            textureShader->render();
        }
    }

    simpleShader->beginRender(glassVertices, 4, 4);
    for (std::vector<PhysicsObject *>::iterator iter = physicsService->getObjects()->begin();
         iter != physicsService->getObjects()->end(); iter++) {
        BaseShape *shape = (*iter)->getShape();
        if (shape->type() == 10) {
            Vec2 center = shape->getCenter();
            simpleShader->setMVP((ndk_helper::Mat4(projMat) *
                                  ndk_helper::Mat4::Translation(center.x(), center.y(),
                                                                0.0f) *
                                  ndk_helper::Mat4::RotationZ(-shape->getAngel())).Ptr());
            GLushort indices[] = {0, 1, 2, 0, 2, 3};
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
        }
    }
}

PhysicsService *GameField::getPhysicsService() {
    return physicsService;
}
