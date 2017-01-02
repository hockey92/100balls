#ifndef INC_100BALLS_RENDERERFACTORY_H
#define INC_100BALLS_RENDERERFACTORY_H

#include <vector>
#include <Mutex.h>
#include "GeometryRenderer.h"
#include "GLTextureRenderer.h"
#include "FontRenderer.h"

class RendererFactory {
public:
    virtual GeometryRenderer *createGeometryRenderer(float *vertices, int size) = 0;

    virtual Renderer *createTextureRenderer(float w, float h, std::string fileName) = 0;

    virtual Renderer *createTextureRenderer(float *vertices, std::string fileName) = 0;

    virtual FontRenderer *createFontRenderer() = 0;
};

#endif //INC_100BALLS_RENDERERFACTORY_H
