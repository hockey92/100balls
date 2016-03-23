#ifndef NATIVE_ACTIVITY_DRAWABLE_H
#define NATIVE_ACTIVITY_DRAWABLE_H

#include "Shader.h"
#include "TextureShader.h"

struct DrawableDate {
    DrawableDate(Shader *simpleShader, TextureShader *textureShader, float *projMat)
            : simpleShader(simpleShader),
              textureShader(textureShader),
              projMat(projMat) { }

    Shader *simpleShader;
    TextureShader *textureShader;
    float *projMat;
};

class Drawable {
public:
    virtual void draw(const DrawableDate &drawableDate) = 0;

    virtual unsigned int type() = 0;
};

#endif //NATIVE_ACTIVITY_DRAWABLE_H
