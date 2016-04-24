#ifndef NATIVE_ACTIVITY_GAMEOVERSCREEN_H
#define NATIVE_ACTIVITY_GAMEOVERSCREEN_H

#include "TextureShader.h"
#include "VertexBuff.h"
#include "Texture.h"
#include "PhysicsObject.h"
#include "GamePhysicsService.h"
#include "Font.h"
#include "ScreenElement.h"
#include "Operationable.h"
#include "Button.h"

class GameOverScreen : public ScreenElement {
public:
    GameOverScreen();

    ~GameOverScreen();

    bool init();

    void draw(float *projMat, Shader *simpleShader, TextureShader *textureShader);

    bool doOperation(void *data);

    void setFinalScore(unsigned int finalScore);

private:
    Texture *texture;
    Font *font;
    unsigned int finalScore;
};

#endif //NATIVE_ACTIVITY_GAMEOVERSCREEN_H
