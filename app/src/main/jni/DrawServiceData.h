#ifndef NATIVE_ACTIVITY_DRAWSERVICEDATA_H
#define NATIVE_ACTIVITY_DRAWSERVICEDATA_H

#include "Initializer.h"
#include "PhysicsObject.h"
#include "Drawable.h"
#include <vector>

class DrawServiceData {
public:
    DrawServiceData(Initializer *initializer);

    virtual ~DrawServiceData();

    bool init();

    void add(Drawable *drawable);

    void draw(Shader *simpleShader, TextureShader *textureShader, float *projMat);

private:
    Initializer *initializer;
    std::vector<Drawable *> objectsToDraw;
};

#endif //NATIVE_ACTIVITY_DRAWSERVICEDATA_H
