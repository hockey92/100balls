#include <vecmath.h>
#include "Button.h"
#include "FileBuf.h"
#include "TouchEventData.h"
#include "AABB.h"

Button::Button(const AABB &aabb, const Vec2 &center) : pushed(false), center(center),
                                                       command(NULL) {
    this->aabb = new AABB(aabb);
    this->aabb->move(center);
    font = new Font(new TGAImage(FileBuf::getInstance()->getFontImage()));
}

bool Button::init() {

    buttonVertex = new VertexBuf(*aabb, 0.5f);

    font->init();

    return true;
}

void Button::doFrame(float *projMat, Shader *simpleShader, TextureShader *textureShader) {

    simpleShader->beginRender(buttonVertex, 4, 4);

    GLushort indices[] = {0, 1, 2, 0, 2, 3};

    simpleShader->setMVP(projMat);
    simpleShader->setColor(1.0f, 0.0f, 0.0f, 0.5f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

    simpleShader->setMVP((pushed
                          ? ndk_helper::Mat4(projMat)
                          : ndk_helper::Mat4(projMat) *
                            ndk_helper::Mat4::Translation(-0.02f, 0.02f, 0.0f)).Ptr());
    simpleShader->setColor(1.0f, 0.0f, 0.0f, 1.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    simpleShader->endRender();

    font->renderText(text, textureShader, projMat,
                     pushed ? aabb->getCenter() : aabb->getCenter() + Vec2(-0.0f, 0.01f));
}

bool Button::doOperation(void *data) {
    TouchEventData *eventData = (TouchEventData *) data;
    switch (eventData->type) {
        case EVENT_DOWN:
            if (!pushed) {
                if (aabb->isPointBelong(eventData->position)) {
                    pushed = true;
                    touchId = eventData->touchId;
                    return true;
                }
            }
            break;
        case EVENT_UP:
            if (pushed) {
                pushed = false;
                if (aabb->isPointBelong(eventData->position) && command) {
                    command->execute(this);
                    return true;
                }
            }
            break;
        default:
            break;
    }
    return false;
}

Button::~Button() {
    if (aabb) {
        delete aabb;
    }
}

Button *Button::setText(const std::string &text) {
    this->text = text;
    return this;
}

void Button::setCommand(Command *command) {
    this->command = command;
}
