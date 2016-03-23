#include "DrawServiceData.h"

DrawServiceData::DrawServiceData(Initializer *initializer) : initializer(initializer) { }

void DrawServiceData::add(Drawable *drawable) {
    objectsToDraw.push_back(drawable);
}

void DrawServiceData::draw(Shader *simpleShader, TextureShader *textureShader, float *projMat) {
    initializer->startRender(simpleShader, textureShader);
    for (int i = 0; i < objectsToDraw.size(); i++) {
        objectsToDraw[i]->draw(DrawableDate(simpleShader, textureShader, projMat));
    }
}

bool DrawServiceData::init() {
    return initializer->init();
}

DrawServiceData::~DrawServiceData() {
    if (initializer) {
        delete initializer;
    }
}
