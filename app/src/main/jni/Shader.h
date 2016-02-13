#ifndef NATIVE_ACTIVITY_SHADER_H
#define NATIVE_ACTIVITY_SHADER_H

class Shader {
protected:
    int vertShader, fragShader, program;
    int MVPMatrix;
    int positionAttrib;

public:
    Shader();

    virtual ~Shader();

    virtual void compile();

    void bindShader();

    void unbindShader();

    // Prepares to render the given geometry.
    virtual void beginRender(/*VertexBuf *vbuf*/);

    // Renders one copy of the prepared geometry, given a model-view-projection matrix.
//    inline void Render(glm::mat4 *mvpMat) {
//        Render(NULL, mvpMat);
//    }

    // Renders a subset (given by the index buffer) of the prepared geometry, using
    // the given model-view-projection matrix.
//    virtual void Render(IndexBuf *ibuf, glm::mat4* mvpMat);

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

    // Must return the vertex shader's GLSL source
    virtual const char *getVertexShaderSource() = 0;

    // Must return the fragment shader's GLSL source
    virtual const char *getFragmentShaderSource() = 0;

    // Must return the shader's name (used for debug/logging purposes)
    virtual const char *getShaderName() = 0;
};

#endif //NATIVE_ACTIVITY_SHADER_H
