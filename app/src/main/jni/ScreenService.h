#ifndef PLATFORMER_SCREENSERVICE_H
#define PLATFORMER_SCREENSERVICE_H

#include <vector>
#include <OrthogonalMatrix.h>
#include "Map.h"
#include "BaseShape.h"
#include "GLObject.h"
#include "Shader.h"
#include "TextureShader.h"
#include "RendererFactory.h"
#include "ObjectAccessor.h"

typedef void *(*ScreenServiceCallbackFunc)(void *);

class ScreenService {
public:
    ScreenService(ObjectAccessor<File> *fileAccessor);

    void beforeDraw();

    void draw(GLObject *glObject);

    void surfaceChanged(float w, float h);

    void surfaceCreated();

    Vec2 convertToGameCoordinates(float x, float y);

    Vec2 getGameCoordinates();

    RendererFactory *getRendererFactory();

    void addSurfaceChangedCallbackFunc(ScreenServiceCallbackFunc func);

private:
    Shader shader;
    TextureShader textureShader;

    RendererFactory *rendererFactory;

    std::vector<ScreenServiceCallbackFunc> surfaceChangedCallbackFuncs;

    OrthogonalMatrix orthogonalMatrix;

    Vec2 physicalScreenSize;

    void compileShaders();
};

#endif //PLATFORMER_SCREENSERVICE_H
