#ifndef NATIVE_ACTIVITY_APPLICATION_H
#define NATIVE_ACTIVITY_APPLICATION_H

#include <jni.h>
#include <EGL/egl.h>

#include <android/input.h>

class Application {
public:
    Application(struct android_app *app);

    void loop();

    ~Application();

    void handleCommand(int32_t cmd);
    bool handleInput(AInputEvent *event);

private:
    struct android_app *app;

    // EGL stuff
    EGLDisplay mEglDisplay;
    EGLSurface mEglSurface;
    EGLContext mEglContext;
    EGLConfig mEglConfig;

    // variables to track Android lifecycle:
    bool mHasFocus, mIsVisible, mHasWindow;

    // are our OpenGL objects (textures, etc) currently loaded?
    bool mHasGLObjects;

    // android API version (0 if not yet queried)
    int mApiVersion;

    bool initDisplay();

    bool initSurface();

    bool initContext();

    bool isAnimating();

    void doFrame();

    bool prepareToRender();

    bool handleEglError(EGLint error);

// kill context
    void killContext();
    void killSurface();
    void killDisplay(); // also causes context and surface to get killed

    bool initGLObjects();
    void killGLObjects();

    void configureOpenGL();
};

#endif

