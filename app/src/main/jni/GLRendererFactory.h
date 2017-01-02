#ifndef INC_100BALLS_GLRENDERERFACTORY_H
#define INC_100BALLS_GLRENDERERFACTORY_H

#include <vector>
#include <Mutex.h>
#include "RendererFactory.h"
#include "GLGeometryRenderer.h"
#include "TextureShader.h"
#include "ObjectAccessor.h"
#include "GLFontRenderer.h"

class GLRendererFactory : public RendererFactory {
public:
    GLRendererFactory(Shader *shader, TextureShader *textureShader,
                      ObjectAccessor<File> *fileAccessor, OrthogonalMatrix *orthogonalMatrix);

    GLGeometryRenderer *createGeometryRenderer(float *vertices, int size);

    GLTextureRenderer *createTextureRenderer(float w, float h, std::string fileName);

    GLTextureRenderer *createTextureRenderer(float *vertices, std::string fileName);

    GLFontRenderer *createFontRenderer();

private:
    Shader *shader;
    TextureShader *textureShader;
    ObjectAccessor<Texture> *textureAccessor;

    std::vector<VertexBuff *> vertexBuffs;

    VertexBuff *getVertexBuff(float *vertices, int size);

    OrthogonalMatrix *orthogonalMatrix;

    Font *font;
};

#endif //INC_100BALLS_GLRENDERERFACTORY_H
