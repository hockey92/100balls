#ifndef NATIVE_ACTIVITY_GAMEFIELD_H
#define NATIVE_ACTIVITY_GAMEFIELD_H

#include "TextureShader.h"
#include "VertexBuf.h"
#include "Texture.h"
#include "PhysicsObject.h"
#include "PhysicsService.h"

class GameField {
public:
    GameField(PhysicsService *physicsService) : physicsService(NULL) { }

    bool init();

    void doFrame(float *projMat);

    PhysicsService *getPhysicsService();

private:
    PhysicsService *physicsService;
    TextureShader *textureShader;
    Shader *simpleShader;
    VertexBuf *circleVertices;
    VertexBuf *glassVertices;
    VertexBuf *containerVertices;
    Texture *texture;
};

#endif //NATIVE_ACTIVITY_GAMEFIELD_H
