#ifndef NATIVE_ACTIVITY_PHYSICSSERVER_H
#define NATIVE_ACTIVITY_PHYSICSSERVER_H

#include <vector>
#include <stack>
#include <pthread.h>
#include "PhysicsObject.h"
#include "BaseShape.h"
#include "BasePhysicsService.h"
#include "GlassPhysicsObject.h"

class PhysicsService : public BasePhysicsService {
public:
    PhysicsService();

    void open();

    void close();

    void draw(float *projMat, Shader *simpleShader, VertexBuf *vertexBuf);

protected:
    virtual void doActionBefore();

    virtual void doActionAfter();

private:
    PhysicsObject *gate;
    std::stack<PhysicsObject *> frozenCircles;
    std::stack<GlassPhysicsObject *> frozenGlasses;

    std::vector<CirclePhysicsObject *> circles;
    std::vector<GlassPhysicsObject *> glasses;
    PhysicsObject *container;
    GlassPhysicsObject *firstGlass;

    GlassPath glassPath;

    void addCircles(float initX, float initY, float direction, float r,
                    float distanceBetweenCircles, bool active, int numOfCircles);

    void checkFrozenGlasses();
};

#endif //NATIVE_ACTIVITY_PHYSICSSERVER_H