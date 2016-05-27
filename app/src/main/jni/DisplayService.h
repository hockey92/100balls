#ifndef NATIVE_ACTIVITY_DISPLAYSERVICE_H
#define NATIVE_ACTIVITY_DISPLAYSERVICE_H

#include <EGL/egl.h>
#include "ScreenManager.h"

class DisplayService : public Operationable {
public:
    DisplayService(struct android_app *app);

    bool doOperation(void *data);

    bool isAnimating();

    bool hasFocus() { return _hasFocus; }

    bool isVisible() { return _isVisible; }

    bool hasWindow() { return _hasWindow; }

    float getW() { return screenW; }

    float getH() { return screenH; }

    bool hasWindow(bool hasWindow) { _hasWindow = hasWindow; }

    bool hasFocus(bool hasFocus) { _hasFocus = hasFocus; }

    bool isVisible(bool isVisible) { _isVisible = isVisible; }

    struct android_app *app;

    ScreenManager *screenManager;

    EGLDisplay eglDisplay;
    EGLSurface eglSurface;
    EGLContext eglContext;
    EGLConfig eglConfig;

    float screenW;
    float screenH;

    bool _hasFocus, _isVisible, _hasWindow;

    bool hasGLObjects;

    bool initDisplay();

    bool initSurface();

    bool initContext();

    bool prepareToRender();

    void doFrame();

    bool initGLObjects();

    void killGLObjects();

    void configureOpenGL();

    bool handleEglError(EGLint error);

    void killContext();

    void killSurface();

    void killDisplay(); // also causes context and surface to get killed

};

#endif //NATIVE_ACTIVITY_DISPLAYSERVICE_H
