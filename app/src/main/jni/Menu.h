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
};

#endif //NATIVE_ACTIVITY_MENU_H
