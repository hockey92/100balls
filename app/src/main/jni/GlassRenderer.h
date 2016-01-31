#ifndef NATIVE_ACTIVITY_GLASSRENDERER_H
#define NATIVE_ACTIVITY_GLASSRENDERER_H

#include "Renderer.h"

class GlassRenderer : public Renderer {

public:
    GlassRenderer();

protected:
    void innerRender(float* pm);

private:
    Vertex* vertices;
};

#endif //NATIVE_ACTIVITY_GLASSRENDERER_H
