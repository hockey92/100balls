#ifndef NATIVE_ACTIVITY_GLASSINITIALIZER_H
#define NATIVE_ACTIVITY_GLASSINITIALIZER_H

#include "Initializer.h"

class GlassInitializer : public Initializer {
public:
    GlassInitializer();

    ~GlassInitializer();

    bool init();

    void startRender(Shader *simpleShader, TextureShader *textureShader);

private:
    VertexBuff *glassVertexBuff;
    float *vertices;
};

#endif //NATIVE_ACTIVITY_GLASSDRAWABLE_H
