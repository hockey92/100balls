#include <stddef.h>
#include "Context.h"

Context *Context::instance = NULL;

Context::Context(float w, float h) {

    float rel = h / w;

    relW = 1.0f;
    relH = rel;
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
    return relW;
}

float Context::getH() {
    return relH;
}
