#ifndef INC_100BALLS_GLGEOMETRYRENDERER_H
#define INC_100BALLS_GLGEOMETRYRENDERER_H

#include <OrthogonalMatrix.h>
#include "GeometryRenderer.h"
#include "Shader.h"

class GLGeometryRenderer : public GeometryRenderer {
public:
    GLGeometryRenderer(float *vertices, int size, Shader *shader, OrthogonalMatrix *orthogonalMatrix);

    GLGeometryRenderer(VertexBuff* vertexBuff, Shader *shader, OrthogonalMatrix *orthogonalMatrix);

    virtual void render(unsigned short *verticesOrder, int size);

private:
    VertexBuff *vertexBuff;
    Shader *shader;
    OrthogonalMatrix *orthogonalMatrix;
};

#endif //INC_100BALLS_GLGEOMETRYRENDERER_H
