#ifndef NATIVE_ACTIVITY_GAMEFIELD_H
#define NATIVE_ACTIVITY_GAMEFIELD_H

#include "TextureShader.h"
#include "VertexBuff.h"
#include "Texture.h"
#include "PhysicsObject.h"
#include "PhysicsService.h"
#include "Font.h"
#include "ScreenElement.h"
#include "Operationable.h"
#include "Button.h"

class GameField : public ScreenElement {
public:
    GameField();
    ~GameField();

    bool init();

    void draw(float *projMat, Shader *simpleShader, TextureShader *textureShader);

    bool doOperation(void *data);

private:
    PhysicsService *physicsService;
    VertexBuff *circleVertices;
    VertexBuff *glassVertices;
    VertexBuff *containerVertices;
    Texture *texture;
    Font* font;
};

#endif //NATIVE_ACTIVITY_GAMEFIELD_H
