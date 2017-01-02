#ifndef INC_100BALLS_GLTEXTURERENDERER_H
#define INC_100BALLS_GLTEXTURERENDERER_H

#include <OrthogonalMatrix.h>
#include "Renderer.h"
#include "Texture.h"
#include "VertexBuff.h"
#include "TextureShader.h"

class GLTextureRenderer : public Renderer {
public:
    GLTextureRenderer(VertexBuff *vertexBuff,
                      Texture *texture,
                      TextureShader *shader,
                      OrthogonalMatrix *orthogonalMatrix);

    virtual void render();

private:
    Texture *texture;
    VertexBuff *vertexBuff;
    TextureShader *shader;
    OrthogonalMatrix *orthogonalMatrix;
};

#endif //INC_100BALLS_GLTEXTURERENDERER_H
