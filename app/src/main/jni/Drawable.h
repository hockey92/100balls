#ifndef NATIVE_ACTIVITY_DRAWABLE_H
#define NATIVE_ACTIVITY_DRAWABLE_H

#include "Shader.h"
#include "TextureShader.h"
#include "Initializer.h"

struct DrawableData {
    DrawableData(Shader *simpleShader, TextureShader *textureShader, float *projMat)
            : simpleShader(simpleShader),
              textureShader(textureShader),
              projMat(projMat) { }

    Shader *simpleShader;
    TextureShader *textureShader;
    float *projMat;
};

class Drawable {
public:
    virtual void draw(const DrawableData &drawableDate) = 0;

    virtual unsigned int type() = 0;

    virtual bool init() { }

    virtual Initializer *createInitializer() {
        return NULL;
    }
};

#endif //NATIVE_ACTIVITY_DRAWABLE_H
