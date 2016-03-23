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

class Button : public ScreenElement {
public:
    Button(const AABB &aabb, const Vec2 &center);

    ~Button();

    bool init();

    void doFrame(float *projMat, Shader *simpleShader, TextureShader *textureShader);

    bool doOperation(void *data);

    Button *setText(const std::string &text);

    void setCommand(Command *command);

private:
    VertexBuff *buttonVertex;
    Font *font;
    bool pushed;
    int touchId;
    AABB *aabb;
    Vec2 center;
    std::string text;
    Command *command;
};

#endif //NATIVE_ACTIVITY_MENU_H
