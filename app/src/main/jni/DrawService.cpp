#include "DrawService.h"

void DrawService::add(Drawable *drawable) {

    unsigned int type = drawable->type();

    std::map<int, DrawServiceData *>::iterator pos = dataToDraw.find(type);
    if (pos == dataToDraw.end()) {
        Initializer *initializer = drawable->createInitializer();
        if (initializer != NULL) {
            pos = dataToDraw.insert(std::pair<int, DrawServiceData *>(type, new DrawServiceData(initializer))).first;
        }
    }
    if (pos != dataToDraw.end()) {
        pos->second->add(drawable);
    }
}

bool DrawService::init() {
    for (std::map<int, DrawServiceData *>::iterator iter = dataToDraw.begin(); iter != dataToDraw.end(); ++iter) {
        iter->second->init();
    }
}

void DrawService::draw(Shader *simpleShader, TextureShader *textureShader, float *projMat) {
    for (std::map<int, DrawServiceData *>::iterator iter = dataToDraw.begin(); iter != dataToDraw.end(); ++iter) {
        iter->second->draw(simpleShader, textureShader, projMat);
    }
}
