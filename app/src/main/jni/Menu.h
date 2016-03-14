#ifndef NATIVE_ACTIVITY_MENU_H
#define NATIVE_ACTIVITY_MENU_H

#include "Circle.h"
#include "Button.h"
#include "ScreenElement.h"
#include <vector>

class Menu : public ScreenElement {
public:
    Menu();

    void doFrame(float *projMat, Shader *simpleShader, TextureShader *textureShader);

    bool doOperation(void *data);

    float getSlide() const;

    void setSlide(float slideX);

    float getSliceDirection() const;

    void setSlideDirection(float sliceDirection);

    virtual bool init();

private:
    float slideX;
    float slideDirection;
    VertexBuf *blackScreen;
};

#endif //NATIVE_ACTIVITY_MENU_H
