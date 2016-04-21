#ifndef NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H
#define NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H

#include <vector>
#include <pthread.h>
#include "PhysicsObject.h"
#include "BaseShape.h"

enum {
    STOPPED, PROCESSING, PAUSED
};

class BasePhysicsService {
public:
    BasePhysicsService();

    void nextFrame();

    int getStatus();

    void setStatus(int status);

protected:
    std::vector<PhysicsObject *> physicsObjects;

    virtual void doActionBefore() { }

    virtual void doActionAfter() { }

private:

    int status;
};

#endif //NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H
