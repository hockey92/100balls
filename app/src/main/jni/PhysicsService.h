#ifndef NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H
#define NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H

#include <vector>
#include <pthread.h>
#include "PhysicsObject.h"
#include "BaseShape.h"
#include "Constraint.h"
#include "IThread.h"
#include "AudioService.h"
#include "CollisionInfo.h"
#include "CollisionInfo.h"

enum {
    STOPPED, PROCESSING, PAUSED
};

class PhysicsService : public IThread {
public:
    PhysicsService();

    virtual ~PhysicsService();

    void nextFrame();

    int getStatus();

    void setStatus(int status);

protected:
    virtual void doActionBefore() { }

    virtual void doActionAfter() { }

    void innerRun();

    void addPhysicsObjects(PhysicsObject *physicsObject);

    pthread_mutex_t mutex;

private:

    static double now() {
        struct timespec res;
        clock_gettime(CLOCK_REALTIME, &res);
        return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;
    }

    std::vector<PhysicsObject *> physicsObjects;

    int status;

    std::vector<Constraint> constraints;

    CollisionInfo* collisionInfos[10000000];
};

#endif //NATIVE_ACTIVITY_BASEPHYSICSSERVICE_H
