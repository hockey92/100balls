#ifndef NATIVE_ACTIVITY_MENU_H
#define NATIVE_ACTIVITY_MENU_H

#include "Circle.h"
#include "Button.h"
#include "ScreenElement.h"
#include <vector>

class Menu : public ScreenElement {
public:
    Menu();

    void doFrame(float *projMat);

    bool doOperation(void *data);

    float getSlide() const;

    void setSlide(float slideX);

    float getSliceDirection() const;

    void setSlideDirection(float sliceDirection);

private:
    float slideX;
    float slideDirection;
};

#endif //NATIVE_ACTIVITY_MENU_H
