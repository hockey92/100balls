#include <vecmath.h>
#include "GameField.h"
#include "FileBuf.h"

void GameField::init() {
    textureShader = new TextureShader();
    textureShader->compile();

    float r = 0.06f;

    GLfloat vertices[] = {-r, -r, 0.0f, 1.0f, //vertex coordinates
                          0.0f, 0.0f, //texture coordinates
                          -r, r, 0.0f, 1.0f,
                          0.0f, 1.0f,
                          r, r, 0.0f, 1.0f,
                          1.0f, 1.0f,
                          r, -r, 0.0f, 1.0f,
                          1.0f, 0.0f};

    vertexBuf = new VertexBuf(&vertices[0], 24 * sizeof(float));
    texture = new Texture(FileBuf::getInstance()->getFile());
}

void GameField::doFrame(float* projMat) {

    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    physicsService->nextFrame();

    textureShader->beginRender(vertexBuf);
    textureShader->setTexture(texture);

    for (std::vector<PhysicsObject *>::iterator iter = physicsService->getObjects()->begin(); iter != physicsService->getObjects()->end(); iter++) {
        BaseShape* shape = (*iter)->getShape();
        if (shape->type() == 1) {
            Vec2 center = shape->getCenter();
            textureShader->setMVP((ndk_helper::Mat4(projMat) *
                                   ndk_helper::Mat4::Translation(center.x(), center.y(),
                                                                 0.0f)).Ptr());
            textureShader->render();
        }
    }
}
