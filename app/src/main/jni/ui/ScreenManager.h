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

private:
    std::vector<ScreenElement *> screens;
    int currentScreen;

    friend class StartButtonCommand;
    friend class PauseButtonCommand;
};

#endif //NATIVE_ACTIVITY_SCREENMANAGER_H
