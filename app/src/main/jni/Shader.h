#ifndef NATIVE_ACTIVITY_SHADER_H
#define NATIVE_ACTIVITY_SHADER_H

#include "VertexBuf.h"

class Shader {
protected:
    int vertShader, fragShader, program;
    int MVPMatrix;
    int positionAttrib;
    VertexBuf *preparedVertexBuf;

public:
    Shader();

    virtual ~Shader();

    virtual void compile();

    void bindShader();

    void unbindShader();

    virtual void beginRender(VertexBuf *vbuf);

    void setMVP(float* mvp);

    // Renders one copy of the prepared geometry, given a model-view-projection matrix.
//    inline void Render(glm::mat4 *mvpMat) {
//        Render(NULL, mvpMat);
//    }

    // Renders a subset (given by the index buffer) of the prepared geometry, using
    // the given model-view-projection matrix.
    virtual void render();

    // Finishes rendering (call this after you're done making calls to Render())
    virtual void endRender();

    // Convenience method to render a single copy of a geometry.
//    inline void RenderSimpleGeom(glm::mat4* mvpMat, SimpleGeom *sg) {
//        beginRender(sg->vbuf);
//        Render(sg->ibuf, mvpMat);
//        endRender();
//    }
protected:
    // Push MVP matrix to the shader
//    void PushMVPMatrix(glm::mat4 *mat);

    // Push the vertex positions to the shader
    void PushPositions(int vbo_offset, int stride);

    virtual const char *getVertexShaderSource();

    virtual const char *getFragmentShaderSource();

    virtual const char *getShaderName();
};

#endif //NATIVE_ACTIVITY_SHADER_H
