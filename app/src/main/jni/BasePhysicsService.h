#ifndef NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H
#define NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H

#include <vector>
#include <pthread.h>
#include "PhysicsObject.h"
#include "BaseShape.h"

class BasePhysicsService {
public:
    BasePhysicsService() : paused(false) { }

    void nextFrame();

    bool isPaused();

    void setPaused(bool paused);

protected:
    std::vector<PhysicsObject *> physicsObjects;

    virtual void doActionBefore() { }

    virtual void doActionAfter() { }

private:
    bool paused;
};

#endif //NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H
