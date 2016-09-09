#include "Context.h"
#include "GamePhysicsService.h"

Context *Context::instance = NULL;

Context::Context(float w, float h) : screen(Screen(w, h)) {
    basePhysicsService = NULL;
    drawService = NULL;
    callbackService = NULL;
    scoreService = NULL;
}

Context *Context::getInstance() {
    return Context::instance;
}

void Context::init(float w, float h) {
    if (Context::instance == NULL) {
        Context::instance = new Context(w, h);
    }
}

float Context::getW() {
    return screen.w();
}

float Context::getH() {
    return screen.h();
}

BasePhysicsService *Context::getPhysicsService() {
    if (basePhysicsService == NULL) {
        basePhysicsService = new GamePhysicsService(getW(), getH(), getDrawService());
//        basePhysicsService->start();
    }
    return basePhysicsService;
}

DrawService *Context::getDrawService() {
    if (drawService == NULL) {
        drawService = new DrawService();
    }
    return drawService;
}

CallbackService *Context::getCallbackService() {
    if (callbackService == NULL) {
        callbackService = new CallbackService();
    }
    return callbackService;
}

ScoreService *Context::getScoreService() {
    if (scoreService == NULL) {
        scoreService = new ScoreService();
    }
    return scoreService;
}

float *Context::getProjMat() const {
    return screen.projMat();
}

float Context::getRealW() {
    return screen.realW();
}

float Context::getRealH() {
    return screen.realH();
}
