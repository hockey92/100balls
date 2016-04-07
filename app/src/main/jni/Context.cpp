#include "Context.h"
#include "PhysicsService.h"

Context *Context::instance = NULL;

Context::Context(float w, float h) : screen(Screen(1.0f, h / w)) {
    basePhysicsService = NULL;
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
        basePhysicsService = new PhysicsService(getW(), getH());
    }
    return basePhysicsService;
}
