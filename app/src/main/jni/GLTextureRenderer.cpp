#include "GLTextureRenderer.h"

void GLTextureRenderer::render() {
    vertexBuff->init();
    texture->init();
    shader->beginRender(vertexBuff, 4, 6);
    shader->setTexture(texture);
    shader->setColor(color);
    orthogonalMatrix->setPosition(x, y);
    orthogonalMatrix->setAngle(angel);
    orthogonalMatrix->apply();
    shader->setMVP(orthogonalMatrix->ptr());
    unsigned short verticesOrder[] = {0, 1, 2, 0, 2, 3};
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, verticesOrder);
}

GLTextureRenderer::GLTextureRenderer(VertexBuff *vertexBuff,
                                     Texture *texture,
                                     TextureShader *shader,
                                     OrthogonalMatrix *orthogonalMatrix) {
    this->vertexBuff = vertexBuff;
    this->texture = texture;
    this->shader = shader;
    this->orthogonalMatrix = orthogonalMatrix;
}
