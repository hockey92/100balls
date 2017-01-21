#include "GLObject.h"

int GLObject::numberOfInits = 0;
int GLObject::lastId = -1;
Mutex GLObject::mutex;

GLObject::GLObject() {
    initIndex = 0;
    mutex.lock();
    id = ++lastId;
    mutex.unlock();
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

int GLObject::getId() {
    return id;
}