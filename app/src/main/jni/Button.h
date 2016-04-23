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
#include "CallbackObject.h"

class Button : public ScreenElement, public CallbackObject {
public:
    Button(const AABB &aabb, const Vec2 &center, ButtonDrawable* drawable, std::string buttonId);

    ~Button();

    bool init();

    void draw(float *projMat, Shader *simpleShader, TextureShader *textureShader);

    bool doOperation(void *data);

    Button *setText(const std::string &text);

private:
    ButtonDrawable* drawable;
    Texture *texture;
    Command *command;
    ButtonData buttonData;
};

#endif //NATIVE_ACTIVITY_MENU_H
