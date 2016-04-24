#ifndef NATIVE_ACTIVITY_CONTEXT_H
#define NATIVE_ACTIVITY_CONTEXT_H

#include "BasePhysicsService.h"
#include "Screen.h"
#include "DrawService.h"
#include "CallbackService.h"
#include "ScoreService.h"

class Context {
public:

    static void init(float w, float h);

    static Context *getInstance();

    float getW();

    float getH();

    BasePhysicsService *getPhysicsService();

    DrawService *getDrawService();

    CallbackService *getCallbackService();

    ScoreService *getScoreService();

private:
    Context(float w, float h);

    static Context *instance;

    Screen screen;

    BasePhysicsService *basePhysicsService;

    DrawService *drawService;

    CallbackService *callbackService;

    ScoreService *scoreService;
};

#endif //NATIVE_ACTIVITY_CONTEXT_H
