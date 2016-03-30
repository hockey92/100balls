#ifndef NATIVE_ACTIVITY_BUTTON_H
#define NATIVE_ACTIVITY_BUTTON_H

#include "VertexBuff.h"
#include "Shader.h"
#include "Font.h"
#include "Operationable.h"
#include "AABB.h"
#include "Vec2.h"
#include "ScreenElement.h"
#include "Command.h"
#include "ButtonData.h"
#include "Drawable.h"
#include "ButtonDrawable.h"

class Button : public ScreenElement {
public:
    Button(const AABB &aabb, const Vec2 &center, ButtonDrawable* drawable);

    ~Button();

    bool init();

    void draw(float *projMat, Shader *simpleShader, TextureShader *textureShader);

    bool doOperation(void *data);

    Button *setText(const std::string &text);

    void setCommand(Command *command);

private:
    ButtonDrawable* drawable;
    Texture *texture;
    int touchId;
    Command *command;
    ButtonData buttonData;
};

#endif //NATIVE_ACTIVITY_MENU_H
