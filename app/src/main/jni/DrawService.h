#ifndef NATIVE_ACTIVITY_DRAWSERVICE_H
#define NATIVE_ACTIVITY_DRAWSERVICE_H

#include <map>
#include <vector>
#include "PhysicsObject.h"
#include "Initializer.h"
#include "DrawServiceData.h"

class DrawService {
public:
    void add(Drawable *drawable);

    bool init();

    void draw(Shader *simpleShader, TextureShader *textureShader, float *projMat);

private:
    std::map<int, DrawServiceData *> dataToDraw;
};

#endif //NATIVE_ACTIVITY_DRAWSERVICE_H
