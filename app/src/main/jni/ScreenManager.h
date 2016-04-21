#ifndef NATIVE_ACTIVITY_SCREENMANAGER_H
#define NATIVE_ACTIVITY_SCREENMANAGER_H

#include "ScreenElement.h"
#include "CallbackObject.h"
#include <vector>

class ScreenManager : public ScreenElement, public CallbackObject {
public:
    ScreenManager();

    bool init();

    void draw(float *projMat);

    bool doOperation(void *data);

    void setCurrentScreen(int currentScreen);

    static void callbackPushPauseButton(CallbackObject *callbackObject, void *callbackData);

    static void callbackPushContinueButton(CallbackObject *callbackObject, void *callbackData);

    static void callbackPushStartButton(CallbackObject *callbackObject, void *callbackData);

private:
    ScreenElement *screens[2];
    int currentScreen;
    Shader *simpleShader;
    TextureShader *textureShader;
};

#endif //NATIVE_ACTIVITY_SCREENMANAGER_H
