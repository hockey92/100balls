#include "Application.h"
#include "common.h"
#include "FileBuf.h"
#include "Context.h"
#include "TouchEventData.h"

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
    displayService = new DisplayService(app);
}

Application::~Application() {
    delete displayService;
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
    LOGD("Application: handling command %d.", cmd);
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
            LOGD("Application: APP_CMD_INIT_WINDOW");
            if (app->window != NULL) {
                displayService->hasWindow(true);
                Context::getInstance()->init(ANativeWindow_getWidth(app->window), ANativeWindow_getHeight(app->window));
            }
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is going away -- kill the surface
            LOGD("Application: APP_CMD_TERM_WINDOW");
            displayService->hasWindow(false);
            displayService->killSurface();
            break;
        case APP_CMD_GAINED_FOCUS:
            LOGD("Application: APP_CMD_GAINED_FOCUS");
            displayService->hasFocus(true);
            break;
        case APP_CMD_LOST_FOCUS:
            LOGD("Application: APP_CMD_LOST_FOCUS");
            displayService->hasFocus(false);
            break;
        case APP_CMD_PAUSE:
            LOGD("Application: APP_CMD_PAUSE");
//            mgr->OnPause();
            break;
        case APP_CMD_RESUME:
            LOGD("Application: APP_CMD_RESUME");
//            mgr->OnResume();
            break;
        case APP_CMD_STOP:
            LOGD("Application: APP_CMD_STOP");
            displayService->isVisible(false);
            break;
        case APP_CMD_START:
            LOGD("Application: APP_CMD_START");
            displayService->isVisible(true);
            break;
        case APP_CMD_WINDOW_RESIZED:
        case APP_CMD_CONFIG_CHANGED:
            LOGD("Application: %s", cmd == APP_CMD_WINDOW_RESIZED ? "APP_CMD_WINDOW_RESIZED" : "APP_CMD_CONFIG_CHANGED");
            // Window was resized or some other configuration changed.
            // Note: we don't handle this event because we check the surface dimensions
            // every frame, so that's how we know it was resized. If you are NOT doing that,
            // then you need to handle this event!
            break;
        case APP_CMD_LOW_MEMORY:
            LOGD("Application: APP_CMD_LOW_MEMORY");
            // system told us we have low memory. So if we are not visible, let's
            // cooperate by deallocating all of our graphic resources.
            if (!displayService->hasWindow()) {
                LOGD("Application: trimming memory footprint (deleting GL objects).");
                displayService->killGLObjects();
            }
            break;
        default:
            LOGD("Application: (unknown command).");
            break;
    }

//    LOGD("Application: STATUS: F%d, V%d, W%d, EGL: D %p, S %p, CTX %p, CFG %p", mHasFocus, mIsVisible, mHasWindow, mEglDisplay, mEglSurface, mEglContext, mEglConfig);
}

bool Application::handleInput(AInputEvent *event) {

    if (!displayService->hasWindow() || Context::getInstance() == NULL) {
        return 0;
    }

    if (AKeyEvent_getKeyCode(event) == AKEYCODE_BACK) {
//        ((ScreenManager *) screenManager)->setCurrentScreen((ScreenManager *) screenManager, 0);
        return 1;
    }

    int eventType = AInputEvent_getType(event);
    if (eventType == AINPUT_EVENT_TYPE_MOTION) {
        int intAction = AKeyEvent_getAction(event);
        int action = intAction & AMOTION_EVENT_ACTION_MASK;
        int pointId = intAction & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK;
        pointId >>= 8;

        float xMax = Context::getInstance()->getW();
        float yMax = Context::getInstance()->getH();

        float x = -xMax + xMax * 2.0f * (AMotionEvent_getX(event, pointId) / Context::getInstance()->getRealW());
        float y = yMax - yMax * 2.0f * (AMotionEvent_getY(event, pointId) / Context::getInstance()->getRealH());

        TouchEventData touchEventData(action, Vec2(x, y), pointId);

        if (action == AMOTION_EVENT_ACTION_DOWN) {
            displayService->doOperation(&touchEventData);
        } else if (action == AMOTION_EVENT_ACTION_UP) {
            displayService->doOperation(&touchEventData);
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
        bool wasAnimating = displayService->isAnimating();

        // If not animating, block until we get an event; if animating, don't block.
        while ((ident = ALooper_pollAll(displayService->isAnimating() ? 0 : -1, NULL, &events, (void **) &source)) >= 0) {

            // process event
            if (source != NULL) {
                source->process(app, source);
            }

            if (app->destroyRequested) {
                return;
            }
        }

        if (displayService->isAnimating()) {
            displayService->doFrame();
        }
    }
}
