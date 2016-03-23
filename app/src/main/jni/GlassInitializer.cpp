#include "GlassInitializer.h"
#include "DrawUtils.h"

GlassInitializer::GlassInitializer() : glassVertexBuff(NULL) {
    vertices = new float[8];

    float d = 0.2f;

    float left = -d * 0.8f;
    float down = -d;
    float right = d * 0.8f;
    float up = d;

    vertices[0] = left, vertices[1] = up;
    vertices[2] = 0.65f * left, vertices[3] = down;
    vertices[4] = 0.65f * right, vertices[5] = down;
    vertices[6] = right, vertices[7] = up;
}

bool GlassInitializer::init() {
    float *coordsForShader = DrawUtils::createCoordsForShader(vertices, 0.0f, 4);
    glassVertexBuff = new VertexBuff(coordsForShader, 16 * sizeof(float));
    return true;
}

GlassInitializer::~GlassInitializer() {
    if (vertices) {
        delete vertices;
    }
}

void GlassInitializer::startRender(Shader *simpleShader, TextureShader *textureShader) {
    simpleShader->beginRender(glassVertexBuff, 4, 4);
}
