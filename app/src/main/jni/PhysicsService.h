#ifndef NATIVE_ACTIVITY_PHYSICSSERVER_H
#define NATIVE_ACTIVITY_PHYSICSSERVER_H

#include <vector>
#include <pthread.h>
#include "PhysicsObject.h"
#include "BaseShape.h"

class PhysicsService {
public:
    PhysicsService();

    void nextFrame();

    void draw(float *projection);

    void open();

    void close();

    std::vector<PhysicsObject *> *getObjects() {
        return &physicsObjects;
    }

private:
    std::vector<PhysicsObject *> physicsObjects;
    PhysicsObject *gate;

//    pthread_t threadId;
//
//    static void *threadFunc(void *ptr);
//
//    void run();
};

#endif //NATIVE_ACTIVITY_PHYSICSSERVER_H
