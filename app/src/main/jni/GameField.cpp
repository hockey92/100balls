#include <vecmath.h>
#include "GameField.h"
#include "FileBuf.h"

void GameField::init() {
    textureShader = new TextureShader();
    textureShader->compile();

    simpleShader = new Shader();
    simpleShader->compile();

    float r = 0.06f;

    GLfloat vertices[] = {-r, -r, 0.0f, 1.0f, //vertex coordinates
                          0.0f, 0.0f, //texture coordinates
                          -r, r, 0.0f, 1.0f,
                          0.0f, 1.0f,
                          r, r, 0.0f, 1.0f,
                          1.0f, 1.0f,
                          r, -r, 0.0f, 1.0f,
                          1.0f, 0.0f};

    float container[] = {
            -1.50f, 0.80f, 0.0f, 1.0f,
            -1.50f, -0.20f, 0.0f, 1.0f,
            -0.12f, -0.90f, 0.0f, 1.0f,
            -0.12f, -1.15f, 0.0f, 1.0f,
            0.12f, -1.15f, 0.0f, 1.0f,
            0.12f, -0.90f, 0.0f, 1.0f,
            1.50f, -0.20f, 0.0f, 1.0f,
            1.50f, 0.80f, 0.0f, 1.0f
    };

    float glass[] = {
            -0.23f, 0.30f, 0.1f, 1.0f,
            -0.15f, -0.30f, 0.1f, 1.0f,
            0.15f, -0.30f, 0.1f, 1.0f,
            0.23f, 0.30f, 0.1f, 1.0f
    };

    circleVertices = new VertexBuf(&vertices[0], 24 * sizeof(float));
    containerVertices = new VertexBuf(&container[0], 32 * sizeof(float));
    glassVertices = new VertexBuf(&glass[0], 16 * sizeof(float));
    texture = new Texture(FileBuf::getInstance()->getFile());
}

void GameField::doFrame(float* projMat) {

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    physicsService->nextFrame();

    simpleShader->beginRender(containerVertices, 4, 4);
    textureShader->setMVP(ndk_helper::Mat4(projMat).Ptr());
    GLushort indices[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7};
    glDrawElements(GL_LINES, 14, GL_UNSIGNED_SHORT, indices);

    textureShader->beginRender(circleVertices, 4, 6);
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

    simpleShader->beginRender(glassVertices, 4, 4);
    for (std::vector<PhysicsObject *>::iterator iter = physicsService->getObjects()->begin(); iter != physicsService->getObjects()->end(); iter++) {
        BaseShape* shape = (*iter)->getShape();
        if (shape->type() == 10) {
            Vec2 center = shape->getCenter();
            simpleShader->setMVP((ndk_helper::Mat4(projMat) *
                                   ndk_helper::Mat4::Translation(center.x(), center.y(),
                                                                 0.0f)).Ptr());
            GLushort indices[] = {0, 1, 2, 0, 2, 3};
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
        }
    }
}
