#include <OrthogonalMatrix.h>
#include <DrawUtils.h>
#include "GLRendererFactory.h"
#include "TextureAccessor.h"

GLRendererFactory::GLRendererFactory(
        Shader *shader,
        TextureShader *textureShader,
        ObjectAccessor<File> *fileAccessor,
        OrthogonalMatrix *orthogonalMatrix
) : shader(shader),
    textureShader(textureShader),
    textureAccessor(new TextureAccessor(fileAccessor)),
    orthogonalMatrix(orthogonalMatrix),
    font(new Font(this, fileAccessor)) {

}

GLGeometryRenderer *GLRendererFactory::createGeometryRenderer(float *vertices, int size) {
    int numberOfVertices = size / 2;
    float *realVertices = DrawUtils::createCoordinatesForShader(vertices, 0, numberOfVertices);
    GLGeometryRenderer *result = new GLGeometryRenderer(
            getVertexBuff(realVertices, numberOfVertices * 4),
            shader, orthogonalMatrix);
    delete[] realVertices;
    return result;
}

GLTextureRenderer *GLRendererFactory::createTextureRenderer(float w, float h,
                                                            std::string fileName) {
    float *vertices = DrawUtils::createCoordinatesForTextureShader(-h / 2.f, h / 2.f,
                                                                   -w / 2.f, w / 2.f,
                                                                   0.f, 1.f,
                                                                   0.f, 1.f);
    GLTextureRenderer *result = new GLTextureRenderer(getVertexBuff(vertices, 24),
                                                      textureAccessor->getObject(fileName),
                                                      textureShader,
                                                      orthogonalMatrix);
    delete[] vertices;
    return result;
}

GLTextureRenderer *GLRendererFactory::createTextureRenderer(float *vertices, std::string fileName) {
    return new GLTextureRenderer(getVertexBuff(vertices, 24),
                                 textureAccessor->getObject(fileName),
                                 textureShader,
                                 orthogonalMatrix);
}

GLFontRenderer *GLRendererFactory::createFontRenderer() {
    return new GLFontRenderer(font);
}

VertexBuff *GLRendererFactory::getVertexBuff(float *vertices, int size) {
    for (int i = 0; i < vertexBuffs.size(); i++) {
        VertexBuff *next = vertexBuffs[i];
        if (next->size() != size) {
            continue;
        }
        bool found = true;
        for (int j = 0; j < size; j++) {
            if (vertices[j] != next->get(j)) {
                found = false;
            }
        }
        if (found) {
            return next;
        }
    }
    VertexBuff *vertexBuff = new VertexBuff(vertices, size);
    vertexBuffs.push_back(vertexBuff);
    return vertexBuff;
}
