#ifndef NATIVE_ACTIVITY_PHYSICSSERVER_H
#define NATIVE_ACTIVITY_PHYSICSSERVER_H

#include <vector>
#include <pthread.h>
#include "PhysicsObject.h"
#include "BaseShape.h"
#include "BasePhysicsService.h"

class PhysicsService : public BasePhysicsService {
public:
    PhysicsService();

    void draw(float *projection);

    void open();

    void close();

private:
    PhysicsObject *gate;

    void addCircles(float initX, float initY, float direction, float r,
                                    float distanceBetweenCircles, bool active, int numOfCircles);
};

#endif //NATIVE_ACTIVITY_PHYSICSSERVER_H
