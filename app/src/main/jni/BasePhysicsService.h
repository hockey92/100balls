#ifndef NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H
#define NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H

#include <vector>
#include <pthread.h>
#include "PhysicsObject.h"
#include "BaseShape.h"

class BasePhysicsService {
public:
    BasePhysicsService() { }

    void nextFrame();

    std::vector<PhysicsObject *> *getObjects() {
        return &physicsObjects;
    }

protected:
    std::vector<PhysicsObject *> physicsObjects;

    virtual void doActionBefore() { }

    virtual void doActionAfter() { }
};

#endif //NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H
