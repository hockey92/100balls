#ifndef NATIVE_ACTIVITY_CONTEXT_H
#define NATIVE_ACTIVITY_CONTEXT_H

#include "BasePhysicsService.h"
#include "Screen.h"

class Context {
public:

    static void init(float w, float h);

    static Context *getInstance();

    float getW();

    float getH();

    BasePhysicsService *getPhysicsService();

private:
    Context(float w, float h);

    static Context *instance;

    Screen screen;

    float relW;
    float relH;

    BasePhysicsService *basePhysicsService;
};

#endif //NATIVE_ACTIVITY_CONTEXT_H
