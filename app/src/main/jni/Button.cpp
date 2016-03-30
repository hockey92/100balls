#include <vecmath.h>
#include "Button.h"
#include "FileBuf.h"
#include "TouchEventData.h"

Button::Button(const AABB &aabb, const Vec2 &center, ButtonDrawable *drawable) : command(NULL),
                                                                                 drawable(drawable),
                                                                                 buttonData(
                                                                                         ButtonData(
                                                                                                 aabb,
                                                                                                 center)) {
    this->drawable = drawable;
    drawable->setButtonData(&buttonData);
}

bool Button::init() {

    return drawable->init();

//    float u, d, l, r;
//    buttonData.aabb()->getCoords(l, r, u, d);
//
//    float *vertices = DrawUtils::createCoordsForTextureShader(
//            d, u, l, r, 0, 1, 0, 1
//    );
//
//    buttonVertex = new VertexBuff(*buttonData.aabb(), 0.5f);
//    buttonVertex = new VertexBuff(vertices, 24 * sizeof(float));
//
//    texture = new Texture(TGAImage(FileBuf::getInstance()->getPauseButton()));
//
//    font->init();
//
//    delete[] vertices;
//
//    return true;
}

void Button::draw(float *projMat, Shader *simpleShader, TextureShader *textureShader) {

    drawable->draw(DrawableData(simpleShader, textureShader, projMat));

//    textureShader->beginRender(buttonVertex, 4, 6);
//    textureShader->setMVP(projMat);
//    textureShader->setColor(Color(0.7f, 0.7f, 0.7f, 1.0f));
//    textureShader->setTexture(texture);
//    textureShader->render();
//    textureShader->endRender();
//
//
//------------------------
//    simpleShader->beginRender(buttonVertex, 4, 4);
//
//    simpleShader->setMVP(projMat);
//
//    if (buttonData.pushed()) {
//        GLushort indices[] = {0, 1, 2, 0, 2, 3};
//        simpleShader->setColor(1.0f, 0.0f, 0.0f, 1.0f);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
//    }
//
//    simpleShader->setColor(1.0f, 1.0f, 1.0f, 1.0f);
//    GLushort indices2[] = {0, 1, 1, 2, 2, 3, 3, 0};
//    glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, indices2);
//---------------------
//    simpleShader->setMVP((pushed
//                          ? ndk_helper::Mat4(projMat)
//                          : ndk_helper::Mat4(projMat) *
//                            ndk_helper::Mat4::Translation(-0.02f, 0.02f, 0.0f)).Ptr());
//    simpleShader->setColor(1.0f, 0.0f, 0.0f, 1.0f);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
//    simpleShader->endRender();
//
//    font->renderText(text, textureShader, projMat,
//                     pushed ? aabb->getCenter() : aabb->getCenter() + Vec2(-0.02f, 0.02f));
//------------------------
//    font->setColor(Color(1.0f, 1.0f, 1.0f, 0.0f));
//    font->renderText(buttonData.text(), textureShader, projMat, buttonData.aabb()->getCenter());
}

bool Button::doOperation(void *data) {
    TouchEventData *eventData = (TouchEventData *) data;
    bool pushed = buttonData.pushed();
    AABB *aabb = buttonData.aabb();
    switch (eventData->type) {
        case EVENT_DOWN:
            if (!pushed) {
                if (aabb->isPointBelong(eventData->position)) {
                    buttonData.setPushed(true);
                    touchId = eventData->touchId;
                    return true;
                }
            }
            break;
        case EVENT_UP:
            if (pushed) {
                buttonData.setPushed(false);
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
    if (drawable) {
        delete drawable;
    }
}

Button *Button::setText(const std::string &text) {
    buttonData.setText(text);
    return this;
}

void Button::setCommand(Command *command) {
    this->command = command;
}
