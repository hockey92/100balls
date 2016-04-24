#ifndef NATIVE_ACTIVITY_MENU_H
#define NATIVE_ACTIVITY_MENU_H

#include "Circle.h"
#include "Button.h"
#include "ScreenElement.h"
#include <vector>

class MenuScreen : public ScreenElement, public CallbackObject {
public:
    MenuScreen();

    void draw(float *projMat, Shader *simpleShader, TextureShader *textureShader);

    bool doOperation(void *data);

    float getSlide() const;

    void setSlide(float slideX);

    float getSliceDirection() const;

    void setSlideDirection(float sliceDirection);

    virtual bool init();

    virtual void beforeDraw();

private:
    float slideX;
    float slideDirection;
    VertexBuff *blackScreen;
    Button *continueButton;
};

#endif //NATIVE_ACTIVITY_MENU_H
