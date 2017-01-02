#include "GLObject.h"

int GLObject::numberOfInits = 0;

GLObject::GLObject() {
    initIndex = 0;
}

void GLObject::prepareRender() {
    innerPrepareRender();
}

void GLObject::init() {
    if (initIndex != numberOfInits) {
        innerInit();
        initIndex = numberOfInits;
    }
}

bool operator==(const GLObject &a, const GLObject &b) {
    return a.equals(b);
}

void GLObject::incrementNumberOfInits() {
    ++numberOfInits;
}