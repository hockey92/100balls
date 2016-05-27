#ifndef NATIVE_ACTIVITY_APPLICATION_H
#define NATIVE_ACTIVITY_APPLICATION_H

#include <jni.h>
#include <EGL/egl.h>

#include <android/input.h>
#include "GameScreen.h"
#include "Button.h"
#include "MenuScreen.h"
#include "DisplayService.h"

class Application {
public:
    Application(struct android_app *app);

    void loop();

    virtual ~Application();

    void handleCommand(int32_t cmd);

    bool handleInput(AInputEvent *event);

private:
    struct android_app *app;
    DisplayService *displayService;
};

#endif
