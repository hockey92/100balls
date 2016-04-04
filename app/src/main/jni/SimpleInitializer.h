#ifndef NATIVE_ACTIVITY_GLASSINITIALIZER_H
#define NATIVE_ACTIVITY_GLASSINITIALIZER_H

#include "Initializer.h"
#include "BaseShape.h"
#include "ArrayWrapper.h"

class SimpleInitializer : public Initializer {
public:
    SimpleInitializer(BaseShape* shape);

    bool init();

    void startRender(Shader *simpleShader, TextureShader *textureShader);

private:
    VertexBuff *glassVertexBuff;
    ArrayWrapper vertices;
};

#endif //NATIVE_ACTIVITY_GLASSDRAWABLE_H
