#ifndef NATIVE_ACTIVITY_CHAINRENDERER_H
#define NATIVE_ACTIVITY_CHAINRENDERER_H

#include "Renderer.h"

class ChainRenderer : public Renderer {
public:
    ChainRenderer(float *points, int num);

    ChainRenderer() { }

protected:
    void innerRender(float *pm);

    void initialize(float *points, int num);

private:
    Vertex *vertices;
    int num;
    unsigned short *indices;
};

#endif //NATIVE_ACTIVITY_CHAINRENDERER_H
