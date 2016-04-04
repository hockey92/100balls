#include "SimpleInitializer.h"
#include "DrawUtils.h"

SimpleInitializer::SimpleInitializer(BaseShape *shape) {
    size_t verticesSize = (size_t) shape->verticesSize();
    float temp[verticesSize];
    shape->getVertices(temp);
    vertices.setValues(temp, verticesSize);
}

bool SimpleInitializer::init() {
    float *coordsForShader = DrawUtils::createCoordsForShader(vertices.ptr(), 0.0f,
                                                              vertices.size() / 2);
    glassVertexBuff = new VertexBuff(coordsForShader, vertices.size() * 2 * sizeof(float));
    return true;
}

void SimpleInitializer::startRender(Shader *simpleShader, TextureShader *textureShader) {
    simpleShader->beginRender(glassVertexBuff, 4, 4);
}
