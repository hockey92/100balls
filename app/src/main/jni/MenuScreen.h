#ifndef NATIVE_ACTIVITY_MENU_H
#define NATIVE_ACTIVITY_MENU_H

#include "Circle.h"
#include "Button.h"
#include "ScreenElement.h"
#include <vector>

class MenuScreen : public ScreenElement, public CallbackObject {
public:
    MenuScreen();

    bool doOperation(void *data);

    virtual void beforeDraw();

private:
    Button *continueButton;
};

#endif //NATIVE_ACTIVITY_MENU_H
