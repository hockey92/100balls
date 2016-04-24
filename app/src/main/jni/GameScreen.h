#ifndef NATIVE_ACTIVITY_GAMEFIELD_H
#define NATIVE_ACTIVITY_GAMEFIELD_H

#include "TextureShader.h"
#include "VertexBuff.h"
#include "Texture.h"
#include "PhysicsObject.h"
#include "GamePhysicsService.h"
#include "Font.h"
#include "ScreenElement.h"
#include "Operationable.h"
#include "Button.h"

class GameScreen : public ScreenElement {
public:
    GameScreen();
    ~GameScreen();

    bool init();

    void draw(float *projMat, Shader *simpleShader, TextureShader *textureShader);

    bool doOperation(void *data);

private:
    Texture *texture;
    Font* font;
};

#endif //NATIVE_ACTIVITY_GAMEFIELD_H
