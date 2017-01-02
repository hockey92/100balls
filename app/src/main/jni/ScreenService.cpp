#include <GLES2/gl2.h>
#include "ScreenService.h"
#include "GLRendererFactory.h"
#include "TextureAccessor.h"

ScreenService::ScreenService(ObjectAccessor<File> *fileAccessor) {
    rendererFactory = new GLRendererFactory(&shader,
                                            &textureShader,
                                            fileAccessor,
                                            &orthogonalMatrix);
}

void ScreenService::draw(GLObject *glObject) {
    shader.setMVP(orthogonalMatrix.ptr());

    glObject->init();
    glObject->prepareRender();
    glObject->render();
}

void ScreenService::surfaceCreated() {
    compileShaders();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);

    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glLineWidth(1.5f);

    GLObject::incrementNumberOfInits();
}

void ScreenService::surfaceChanged(float w, float h) {
    glViewport(0, 0, w, h);
    physicalScreenSize = Vec2(w, h);
    orthogonalMatrix.surfaceChanged(w, h);
    for (int i = 0; i < surfaceChangedCallbackFuncs.size(); i++) {
        (*(surfaceChangedCallbackFuncs[i]))(NULL);
    }
}

Vec2 ScreenService::convertToGameCoordinates(float x, float y) {
    float *projMatrix = orthogonalMatrix.ptr();
    return Vec2(
            -1.f * projMatrix[15] + x / physicalScreenSize.x() * 2.f * projMatrix[15],
            1.f * projMatrix[15] / projMatrix[5] -
            y / physicalScreenSize.y() * 2.f * projMatrix[15] / projMatrix[5]
    );
}

void ScreenService::beforeDraw() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

Vec2 ScreenService::getGameCoordinates() {
    return Vec2(orthogonalMatrix.getW(), orthogonalMatrix.getH());
}

void ScreenService::compileShaders() {
    shader.compile();
    textureShader.compile();
}

RendererFactory *ScreenService::getRendererFactory() {
    return rendererFactory;
}

void ScreenService::addSurfaceChangedCallbackFunc(ScreenServiceCallbackFunc func) {
    surfaceChangedCallbackFuncs.push_back(func);
}
