#include "SimpleInitializer.h"
#include "DrawUtils.h"

SimpleInitializer::SimpleInitializer(BaseShape *shape) {
    size_t verticesSize = (size_t) shape->verticesSize();
    float temp[verticesSize];
    shape->getVertices(temp);
    float *coordsForShader = DrawUtils::createCoordsForShader(temp, 0.0f, verticesSize / 2);
    glassVertexBuff = new VertexBuff(coordsForShader, verticesSize * 2);

    delete[] coordsForShader;
}

bool SimpleInitializer::init() {
    glassVertexBuff->init();
    return true;
}

void SimpleInitializer::startRender(Shader *simpleShader, TextureShader *textureShader) {
    simpleShader->beginRender(glassVertexBuff, 4, 4);
}

bool SimpleInitializer::kill() {
    return false;
}
