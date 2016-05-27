#include <GLES/gl.h>
#include "DisplayService.h"
#include "common.h"
#include "Context.h"

#define MAX_GL_ERRORS 200

DisplayService::DisplayService(struct android_app *app) {
    this->app = app;
    eglDisplay = EGL_NO_DISPLAY;
    eglSurface = EGL_NO_SURFACE;
    eglContext = EGL_NO_CONTEXT;
    eglConfig = 0;
    _hasFocus = false, _isVisible = false, _hasWindow = false;
    screenManager = NULL;
}

static const char *_log_opengl_error(GLenum err) {
    switch (err) {
        case GL_NO_ERROR:
            LOGE("OpenGL error: GL_NO_ERROR");
            break;
        case GL_INVALID_ENUM:
            LOGE("OpenGL error: GL_INVALID_ENUM");
            break;
        case GL_INVALID_VALUE:
            LOGE("OpenGL error: GL_INVALID_VALUE");
            break;
        case GL_INVALID_OPERATION:
            LOGE("OpenGL error: GL_INVALID_OPERATION");
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            LOGE("OpenGL error: GL_INVALID_FRAMEBUFFER_OPERATION");
            break;
        case GL_OUT_OF_MEMORY:
            LOGE("OpenGL error: GL_OUT_OF_MEMORY");
            break;
        default:
            LOGE("OpenGL error: error %d", err);
            break;
    }
}

bool DisplayService::initDisplay() {
    if (eglDisplay != EGL_NO_DISPLAY) {
        LOGD("DisplayService: no need to init display (already had one).");
        return true;
    }

    LOGD("DisplayService: initializing display.");
    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (EGL_FALSE == eglInitialize(eglDisplay, 0, 0)) {
        LOGE("DisplayService: failed to init display, error %d", eglGetError());
        return false;
    }
    return true;
}

bool DisplayService::initSurface() {
    ASSERT(eglDisplay != EGL_NO_DISPLAY);

    if (eglSurface != EGL_NO_SURFACE) {
        // nothing to do
        LOGD("DisplayService: no need to init surface (already had one).");
        return true;
    }

    LOGD("DisplayService: initializing surface.");

    EGLint numConfigs, format;

    const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE,
            EGL_OPENGL_ES2_BIT,
            EGL_SURFACE_TYPE,
            EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_SAMPLE_BUFFERS, 1,
            EGL_SAMPLES, 16,
            EGL_NONE};
    eglChooseConfig(eglDisplay, attribs, &eglConfig, 1, &numConfigs);
    eglGetConfigAttrib(eglDisplay, eglConfig, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);

    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, app->window, NULL);
    if (eglSurface == EGL_NO_SURFACE) {
        LOGE("DisplayService: failed to create EGL surface, EGL error %d", eglGetError());
        return false;
    }

    LOGD("DisplayService: successfully initialized surface.");
    return true;
}

bool DisplayService::initContext() {
    ASSERT(eglDisplay != EGL_NO_DISPLAY);

    EGLint attrList[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};

    if (eglContext != EGL_NO_CONTEXT) {
        LOGD("DisplayService: no need to init context (already had one).");
        return true;
    }

    LOGD("DisplayService: initializing context.");

    eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, attrList);
    if (eglContext == EGL_NO_CONTEXT) {
        LOGE("DisplayService: failed to create EGL context, EGL error %d", eglGetError());
        return false;
    }

    LOGD("DisplayService: successfull initialized context.");

    return true;
}

bool DisplayService::prepareToRender() {
    // if we're missing a surface, context, or display, create them
    if (eglDisplay == EGL_NO_DISPLAY || eglSurface == EGL_NO_SURFACE || eglContext == EGL_NO_CONTEXT) {
        // create display if needed
        if (!initDisplay()) {
            LOGE("DisplayService: failed to create display.");
            return false;
        }

        // create surface if needed
        if (!initSurface()) {
            LOGE("DisplayService: failed to create surface.");
            return false;
        }

        // create context if needed
        if (!initContext()) {
            LOGE("DisplayService: failed to create context.");
            return false;
        }

        LOGD("DisplayService: binding surface and context (display %p, surface %p, context %p)", eglDisplay, eglSurface, eglContext);

        // bind them
        if (EGL_FALSE == eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) {
            LOGE("DisplayService: eglMakeCurrent failed, EGL error %d", eglGetError());
            handleEglError(eglGetError());
        }

        // configure our global OpenGL settings
        configureOpenGL();
    }

    int width, height;
    eglQuerySurface(eglDisplay, eglSurface, EGL_WIDTH, &width);
    eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &height);
    Context::init(width, height);

    if (screenManager == NULL) {
        screenManager = new ScreenManager();
    }

    // now that we're sure we have a context and all, if we don't have the OpenGL objects ready, create them.
    if (!hasGLObjects) {
        LOGD("DisplayService: creating OpenGL objects.");
        if (!initGLObjects()) {
            LOGE("DisplayService: unable to initialize OpenGL objects.");
            return false;
        }
    }

    // ready to render
    return true;
}

bool DisplayService::initGLObjects() {
    if (!hasGLObjects) {
        if (!screenManager->init()) {
            return false;
        }
        _log_opengl_error(glGetError());
        hasGLObjects = true;
    }
    return true;
}

void DisplayService::killGLObjects() {
    if (hasGLObjects) {
        screenManager->kill();
        _log_opengl_error(glGetError());
        hasGLObjects = false;
    }
}

void DisplayService::configureOpenGL() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(2.0f);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

bool DisplayService::handleEglError(EGLint error) {
    switch (error) {
        case EGL_SUCCESS:
            // nothing to do
            return true;
        case EGL_CONTEXT_LOST:
            LOGW("DisplayService: egl error: EGL_CONTEXT_LOST. Recreating context.");
            killContext();
            return true;
        case EGL_BAD_CONTEXT:
            LOGW("DisplayService: egl error: EGL_BAD_CONTEXT. Recreating context.");
            killContext();
            return true;
        case EGL_BAD_DISPLAY:
            LOGW("DisplayService: egl error: EGL_BAD_DISPLAY. Recreating display.");
            killDisplay();
            return true;
        case EGL_BAD_SURFACE:
            LOGW("DisplayService: egl error: EGL_BAD_SURFACE. Recreating display.");
            killSurface();
            return true;
        default:
            LOGW("DisplayService: unknown egl error: %d", error);
            return false;
    }
}

void DisplayService::killContext() {
    LOGD("DisplayService: killing context.");

    // since the context is going away, we have to kill the GL objects
    killGLObjects();

    eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

    if (eglContext != EGL_NO_CONTEXT) {
        eglDestroyContext(eglDisplay, eglContext);
        eglContext = EGL_NO_CONTEXT;
    }
    LOGD("DisplayService: Context killed successfully.");
}

void DisplayService::killSurface() {
    LOGD("DisplayService: killing surface.");
    eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    if (eglSurface != EGL_NO_SURFACE) {
        eglDestroySurface(eglDisplay, eglSurface);
        eglSurface = EGL_NO_SURFACE;
    }
    LOGD("DisplayService: Surface killed successfully.");
}

void DisplayService::killDisplay() {
// causes context and surface to go away too, if they are there
    LOGD("DisplayService: killing display.");
    killContext();
    killSurface();

    if (eglDisplay != EGL_NO_DISPLAY) {
        LOGD("DisplayService: terminating display now.");
        eglTerminate(eglDisplay);
        eglDisplay = EGL_NO_DISPLAY;
    }
    LOGD("DisplayService: display killed successfully.");
}

bool DisplayService::isAnimating() {
    return _hasFocus && _isVisible && _hasWindow;;
}

void DisplayService::doFrame() {
    if (!prepareToRender()) {
        LOGD("DisplayService: preparation to render failed.");
        return;
    }

    screenManager->draw(Context::getInstance()->getProjMat());

    if (EGL_FALSE == eglSwapBuffers(eglDisplay, eglSurface)) {
        LOGW("DisplayService: eglSwapBuffers failed, EGL error %d", eglGetError());
        handleEglError(eglGetError());
    }

    GLenum e;
    static int errorsPrinted = 0;
    while ((e = glGetError()) != GL_NO_ERROR) {
        if (errorsPrinted < MAX_GL_ERRORS) {
            _log_opengl_error(e);
            ++errorsPrinted;
            if (errorsPrinted >= MAX_GL_ERRORS) {
                LOGE("DisplayService: TOO MANY OPENGL ERRORS. NO LONGER PRINTING.");
            }
        }
    }
}

bool DisplayService::doOperation(void *data) {
    if (screenManager == NULL) {
        return false;
    }
    return screenManager->doOperation(data);
}
