#ifndef NATIVE_ACTIVITY_SCREENMANAGER_H
#define NATIVE_ACTIVITY_SCREENMANAGER_H

#include "ScreenElement.h"
#include <vector>

class ScreenManager : public ScreenElement {
public:
    ScreenManager();

    bool init();

    void doFrame(float *projMat);

    bool doOperation(void *data);

    void setCurrentScreen(int currentScreen);

private:
    std::vector<ScreenElement *> screens;
    int currentScreen;
};

#endif //NATIVE_ACTIVITY_SCREENMANAGER_H
