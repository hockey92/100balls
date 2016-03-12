#include "Application.h"
#include "common.hpp"
#include "FileBuf.h"
#include "GameCoords.h"
#include "TouchEventData.h"
#include "ScreenManager.h"

#define VERBOSE_LOGGING 1

#if VERBOSE_LOGGING
#define VLOGD LOGD
#else
#define VLOGD
#endif

#define MAX_GL_ERRORS 200

Application::Application(struct android_app *app) {
    this->app = app;
    FileBuf::init(app);
    mEglDisplay = EGL_NO_DISPLAY;
    mEglSurface = EGL_NO_SURFACE;
    mEglContext = EGL_NO_CONTEXT;
    mEglConfig = 0;
    mHasFocus = false, mIsVisible = false, mHasWindow = false;
    physicsService = NULL;//new PhysicsService();
    screenManager = new ScreenManager();//new GameField(physicsService);
}

Application::~Application() {
    killContext();
}

bool Application::initDisplay() {
    if (mEglDisplay != EGL_NO_DISPLAY) {
        LOGD("Application: no need to init display (already had one).");
        return true;
    }

    LOGD("Application: initializing display.");
    mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (EGL_FALSE == eglInitialize(mEglDisplay, 0, 0)) {
        LOGE("Application: failed to init display, error %d", eglGetError());
        return false;
    }
    return true;
}

bool Application::initSurface() {
    ASSERT(mEglDisplay != EGL_NO_DISPLAY);

    if (mEglSurface != EGL_NO_SURFACE) {
        // nothing to do
        LOGD("Application: no need to init surface (already had one).");
        return true;
    }

    LOGD("Application: initializing surface.");

    EGLint numConfigs, format;

    const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE,
            EGL_OPENGL_ES2_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8, EGL_DEPTH_SIZE, 24, EGL_NONE
    };

    // since this is a simple sample, we have a trivial selection process. We pick
    // the first EGLConfig that matches:
    eglChooseConfig(mEglDisplay, attribs, &mEglConfig, 1, &numConfigs);

    // configure native window
    eglGetConfigAttrib(mEglDisplay, mEglConfig, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);

    // create EGL surface
    mEglSurface = eglCreateWindowSurface(mEglDisplay, mEglConfig, app->window, NULL);
    if (mEglSurface == EGL_NO_SURFACE) {
        LOGE("Application: failed to create EGL surface, EGL error %d", eglGetError());
        return false;
    }

    LOGD("Application: successfully initialized surface.");
    return true;
}

static const char *_log_opengl_error(GLenum err) {
    switch (err) {
        case GL_NO_ERROR:
            LOGE("*** OpenGL error: GL_NO_ERROR");
            break;
        case GL_INVALID_ENUM:
            LOGE("*** OpenGL error: GL_INVALID_ENUM");
            break;
        case GL_INVALID_VALUE:
            LOGE("*** OpenGL error: GL_INVALID_VALUE");
            break;
        case GL_INVALID_OPERATION:
            LOGE("*** OpenGL error: GL_INVALID_OPERATION");
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            LOGE("*** OpenGL error: GL_INVALID_FRAMEBUFFER_OPERATION");
            break;
        case GL_OUT_OF_MEMORY:
            LOGE("*** OpenGL error: GL_OUT_OF_MEMORY");
            break;
        default:
            LOGE("*** OpenGL error: error %d", err);
            break;
    }
}

bool Application::initContext() {
    ASSERT(mEglDisplay != EGL_NO_DISPLAY);

    EGLint attrList[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};

    if (mEglContext != EGL_NO_CONTEXT) {
        LOGD("Application: no need to init context (already had one).");
        return true;
    }

    LOGD("Application: initializing context.");

    mEglContext = eglCreateContext(mEglDisplay, mEglConfig, NULL, attrList);
    if (mEglContext == EGL_NO_CONTEXT) {
        LOGE("Application: failed to create EGL context, EGL error %d", eglGetError());
        return false;
    }

    LOGD("Application: successfull initialized context.");

    return true;
}

static void _handle_cmd_proxy(struct android_app *app, int32_t cmd) {
    Application *application = (Application *) app->userData;
    application->handleCommand(cmd);
}

static int _handle_input_proxy(struct android_app *app, AInputEvent *event) {
    Application *application = (Application *) app->userData;
    return application->handleInput(event) ? 1 : 0;
}

void Application::handleCommand(int32_t cmd) {
//    SceneManager *mgr = SceneManager::GetInstance();

    VLOGD("Application: handling command %d.", cmd);
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.
//                    VLOGD("Application: APP_CMD_SAVE_STATE");
//            mApp->savedState = malloc(sizeof(mState));
//            *((ApplicationSavedState *) mApp->savedState) = mState;
//            mApp->savedStateSize = sizeof(mState);
            break;
        case APP_CMD_INIT_WINDOW:
            // We have a window!
//                    VLOGD("Application: APP_CMD_INIT_WINDOW");
            if (app->window != NULL) {
                mHasWindow = true;
                screenW = ANativeWindow_getWidth(app->window);
                screenH = ANativeWindow_getHeight(app->window);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is going away -- kill the surface
//                    VLOGD("Application: APP_CMD_TERM_WINDOW");
            killSurface();
            mHasWindow = false;
            break;
        case APP_CMD_GAINED_FOCUS:
//                    VLOGD("Application: APP_CMD_GAINED_FOCUS");
            mHasFocus = true;
            break;
        case APP_CMD_LOST_FOCUS:
//                    VLOGD("Application: APP_CMD_LOST_FOCUS");
            mHasFocus = false;
            break;
        case APP_CMD_PAUSE:
//                    VLOGD("Application: APP_CMD_PAUSE");
//            mgr->OnPause();
            break;
        case APP_CMD_RESUME:
//                    VLOGD("Application: APP_CMD_RESUME");
//            mgr->OnResume();
            break;
        case APP_CMD_STOP:
//                    VLOGD("Application: APP_CMD_STOP");
            mIsVisible = false;
            break;
        case APP_CMD_START:
//                    VLOGD("Application: APP_CMD_START");
            mIsVisible = true;
            break;
        case APP_CMD_WINDOW_RESIZED:
        case APP_CMD_CONFIG_CHANGED:
//                    VLOGD("Application: %s", cmd == APP_CMD_WINDOW_RESIZED ?
//                                              "APP_CMD_WINDOW_RESIZED" : "APP_CMD_CONFIG_CHANGED");
            // Window was resized or some other configuration changed.
            // Note: we don't handle this event because we check the surface dimensions
            // every frame, so that's how we know it was resized. If you are NOT doing that,
            // then you need to handle this event!
            break;
        case APP_CMD_LOW_MEMORY:
//                    VLOGD("Application: APP_CMD_LOW_MEMORY");
            // system told us we have low memory. So if we are not visible, let's
            // cooperate by deallocating all of our graphic resources.
            if (!mHasWindow) {
//                        VLOGD("Application: trimming memory footprint (deleting GL objects).");
                killGLObjects();
            }
            break;
        default:
//                    VLOGD("Application: (unknown command).");
            break;
    }

//            VLOGD("Application: STATUS: F%d, V%d, W%d, EGL: D %p, S %p, CTX %p, CFG %p",
//                  mHasFocus, mIsVisible, mHasWindow, mEglDisplay, mEglSurface, mEglContext,
//                  mEglConfig);
}

bool Application::handleInput(AInputEvent *event) {
    if (!mHasWindow || GameCoords::getInstance() == NULL) {
        return 0;
    }
    int eventType = AInputEvent_getType(event);
    if (eventType == AINPUT_EVENT_TYPE_MOTION) {
        int intAction = AKeyEvent_getAction(event);
        int action = intAction & AMOTION_EVENT_ACTION_MASK;
        int pointId = intAction & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK;
        pointId >>= 8;

        LOGE("POINT_ID %d", pointId);

        float xMax = GameCoords::getInstance()->getCoords(SCREEN_BORDERS)->getData()[WIDTH];
        float yMax = GameCoords::getInstance()->getCoords(SCREEN_BORDERS)->getData()[HEIGHT];

        float x = -xMax + xMax * 2.0f * (AMotionEvent_getX(event, pointId) / screenW);
        float y = yMax - yMax * 2.0f * (AMotionEvent_getY(event, pointId) / screenH);

        TouchEventData touchEventData(action, Vec2(x, y), pointId);

//        PhysicsService *physicsService = gameField->getPhysicsService();
        if (action == AMOTION_EVENT_ACTION_DOWN) {
            if (screenManager) {
                screenManager->doOperation(&touchEventData);
            }
//            if (physicsService) {
//                physicsService->open();
//            }
        } else if (action == AMOTION_EVENT_ACTION_UP) {
            if (screenManager) {
                screenManager->doOperation(&touchEventData);
            }
//            if (physicsService) {
//                physicsService->close();
//            }
        }

        return 1;
    }
    return 0;
}

void Application::loop() {
    app->userData = this;
    app->onAppCmd = _handle_cmd_proxy;
    app->onInputEvent = _handle_input_proxy;

    while (1) {
        int ident, events;
        struct android_poll_source *source;
        bool wasAnimating = isAnimating();

        // If not animating, block until we get an event; if animating, don't block.
        while ((ident = ALooper_pollAll(isAnimating() ? 0 : -1, NULL, &events,
                                        (void **) &source)) >= 0) {

            // process event
            if (source != NULL) {
                source->process(app, source);
            }

            if (app->destroyRequested) {
                return;
            }
        }

        if (isAnimating()) {
            doFrame();
        }
    }
}

bool Application::isAnimating() {
    return mHasFocus && mIsVisible && mHasWindow;
}

void Application::doFrame() {
    // prepare to render (create context, surfaces, etc, if needed)
    if (!prepareToRender()) {
        // not ready
        VLOGD("Application: preparation to render failed.");
        return;
    }

//    SceneManager *mgr = SceneManager::GetInstance();

    // how big is the surface? We query every frame because it's cheap, and some
    // strange devices out there change the surface size without calling any callbacks...
    int width, height;
    eglQuerySurface(mEglDisplay, mEglSurface, EGL_WIDTH, &width);
    eglQuerySurface(mEglDisplay, mEglSurface, EGL_HEIGHT, &height);

//    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
//
//    if (width != mSurfWidth || height != mSurfHeight) {
//        // notify scene manager that the surface has changed size
//        LOGD("NativeEngine: surface changed size %dx%d --> %dx%d", mSurfWidth, mSurfHeight,
//             width, height);
//        mSurfWidth = width;
//        mSurfHeight = height;
//        mgr->SetScreenSize(mSurfWidth, mSurfHeight);
//        glViewport(0, 0, mSurfWidth, mSurfHeight);
//    }
//
//    // if this is the first frame, install the welcome scene
//    if (mIsFirstFrame) {
//        mIsFirstFrame = false;
//        mgr->RequestNewScene(new WelcomeScene());
//    }
//
//    // render!
//    mgr->DoFrame();

    float pM[16];
    for (int i = 0; i < 16; i++) {
        pM[i] = 0;
    }

    float rel = (float) width / (float) height;

    pM[0] = 1.0f;
    pM[5] = rel;
    pM[10] = -1.0f;
    pM[15] = 1.0f;

    screenManager->doFrame(pM);

    if (EGL_FALSE == eglSwapBuffers(mEglDisplay, mEglSurface)) {
        LOGW("Application: eglSwapBuffers failed, EGL error %d", eglGetError());
        handleEglError(eglGetError());
    }

    GLenum e;
    static int errorsPrinted = 0;
    while ((e = glGetError()) != GL_NO_ERROR) {
        if (errorsPrinted < MAX_GL_ERRORS) {
            _log_opengl_error(e);
            ++errorsPrinted;
            if (errorsPrinted >= MAX_GL_ERRORS) {
                LOGE("*** Application: TOO MANY OPENGL ERRORS. NO LONGER PRINTING.");
            }
        }
    }
}


bool Application::prepareToRender() {
    do {
        // if we're missing a surface, context, or display, create them
        if (mEglDisplay == EGL_NO_DISPLAY || mEglSurface == EGL_NO_SURFACE ||
            mEglContext == EGL_NO_CONTEXT) {

            // create display if needed
            if (!initDisplay()) {
                LOGE("Application: failed to create display.");
                return false;
            }

            // create surface if needed
            if (!initSurface()) {
                LOGE("Application: failed to create surface.");
                return false;
            }

            // create context if needed
            if (!initContext()) {
                LOGE("Application: failed to create context.");
                return false;
            }

            LOGD("Application: binding surface and context (display %p, surface %p, context %p)",
                 mEglDisplay, mEglSurface, mEglContext);

            // bind them
            if (EGL_FALSE ==
                eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext)) {
                LOGE("Application: eglMakeCurrent failed, EGL error %d", eglGetError());
                handleEglError(eglGetError());
            }

            // configure our global OpenGL settings
            configureOpenGL();
        }

        int width, height;
        eglQuerySurface(mEglDisplay, mEglSurface, EGL_WIDTH, &width);
        eglQuerySurface(mEglDisplay, mEglSurface, EGL_HEIGHT, &height);
        GameCoords::init(width, height);

        // now that we're sure we have a context and all, if we don't have the OpenGL
        // objects ready, create them.
        if (!mHasGLObjects) {
            LOGD("Application: creating OpenGL objects.");
            if (!initGLObjects()) {
                LOGE("Application: unable to initialize OpenGL objects.");
                return false;
            }
        }
    } while (0);

    // ready to render
    return true;
}

bool Application::handleEglError(EGLint error) {
    switch (error) {
        case EGL_SUCCESS:
            // nothing to do
            return true;
        case EGL_CONTEXT_LOST:
            LOGW("Application: egl error: EGL_CONTEXT_LOST. Recreating context.");
            killContext();
            return true;
        case EGL_BAD_CONTEXT:
            LOGW("Application: egl error: EGL_BAD_CONTEXT. Recreating context.");
            killContext();
            return true;
        case EGL_BAD_DISPLAY:
            LOGW("Application: egl error: EGL_BAD_DISPLAY. Recreating display.");
            killDisplay();
            return true;
        case EGL_BAD_SURFACE:
            LOGW("Application: egl error: EGL_BAD_SURFACE. Recreating display.");
            killSurface();
            return true;
        default:
            LOGW("Application: unknown egl error: %d", error);
            return false;
    }
}

void Application::killContext() {
    LOGD("Application: killing context.");

    // since the context is going away, we have to kill the GL objects
    killGLObjects();

    eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    if (mEglContext != EGL_NO_CONTEXT) {
        eglDestroyContext(mEglDisplay, mEglContext);
        mEglContext = EGL_NO_CONTEXT;
    }
    LOGD("Application: Context killed successfully.");
}

void Application::killSurface() {
    LOGD("Application: killing surface.");
    eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (mEglSurface != EGL_NO_SURFACE) {
        eglDestroySurface(mEglDisplay, mEglSurface);
        mEglSurface = EGL_NO_SURFACE;
    }
    LOGD("Application: Surface killed successfully.");
}

void Application::killDisplay() {
// causes context and surface to go away too, if they are there
    LOGD("Application: killing display.");
    killContext();
    killSurface();

    if (mEglDisplay != EGL_NO_DISPLAY) {
        LOGD("Application: terminating display now.");
        eglTerminate(mEglDisplay);
        mEglDisplay = EGL_NO_DISPLAY;
    }
    LOGD("Application: display killed successfully.");
}

bool Application::initGLObjects() {
    if (!mHasGLObjects) {
        if (!screenManager->init()) {
            return false;
        }
        _log_opengl_error(glGetError());
        mHasGLObjects = true;
    }
    return true;
}

void Application::killGLObjects() {

}

void Application::configureOpenGL() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
