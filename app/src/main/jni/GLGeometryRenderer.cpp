#include <DrawUtils.h>
#include "GLGeometryRenderer.h"

void GLGeometryRenderer::render(unsigned short *verticesOrder, int size) {
    vertexBuff->init();
    shader->beginRender(vertexBuff, 4, 4);
    shader->setColor(color);
    orthogonalMatrix->setPosition(x, y);
    orthogonalMatrix->setAngle(angel);
    orthogonalMatrix->apply();
    shader->setMVP(orthogonalMatrix->ptr());
    if (filled) {
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, verticesOrder);
    } else {
        glDrawElements(GL_LINES, size, GL_UNSIGNED_SHORT, verticesOrder);
    }
}

GLGeometryRenderer::GLGeometryRenderer(float *vertices,
                                       int size,
                                       Shader *shader,
                                       OrthogonalMatrix *orthogonalMatrix) {
    int numberOfVertices = size / 2;
    vertices = DrawUtils::createCoordinatesForShader(vertices, 0, numberOfVertices);
    this->vertexBuff = new VertexBuff(vertices, numberOfVertices * 4);
    delete[] vertices;
    this->shader = shader;
    this->orthogonalMatrix = orthogonalMatrix;
}

GLGeometryRenderer::GLGeometryRenderer(VertexBuff *vertexBuff,
                                       Shader *shader,
                                       OrthogonalMatrix *orthogonalMatrix) {
    this->vertexBuff = vertexBuff;
    this->shader = shader;
    this->orthogonalMatrix = orthogonalMatrix;
}
