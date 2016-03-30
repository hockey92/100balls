#ifndef NATIVE_ACTIVITY_SCREENMANAGER_H
#define NATIVE_ACTIVITY_SCREENMANAGER_H

#include "ScreenElement.h"
#include <vector>

class ScreenManager : public ScreenElement {
public:
    ScreenManager();

    bool init();

    void draw(float *projMat);

    bool doOperation(void *data);

    void setCurrentScreen(int currentScreen);

private:
    std::vector<ScreenElement *> screens;
    int currentScreen;
    Shader *simpleShader;
    TextureShader *textureShader;
};

#endif //NATIVE_ACTIVITY_SCREENMANAGER_H