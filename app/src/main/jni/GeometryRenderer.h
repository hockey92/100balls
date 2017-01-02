#ifndef INC_100BALLS_GEOMETRYRENDERER_H
#define INC_100BALLS_GEOMETRYRENDERER_H

#include "Color.h"
#include "Renderer.h"

class GeometryRenderer : public Renderer {
public:
    virtual void render(unsigned short *verticesOrder, int size) = 0;

    virtual void render() { }
};

#endif //INC_100BALLS_GEOMETRYRENDERER_H
