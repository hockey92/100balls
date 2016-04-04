#ifndef NATIVE_ACTIVITY_PHYSICSSERVER_H
#define NATIVE_ACTIVITY_PHYSICSSERVER_H

#include <vector>
#include <stack>
#include <pthread.h>
#include "PhysicsObject.h"
#include "BaseShape.h"
#include "BasePhysicsService.h"
#include "GlassGameObject.h"
#include "DrawService.h"
#include "Container.h"
#include "ContainerGameObject.h"

class PhysicsService : public BasePhysicsService, public Drawable {
public:
    PhysicsService(float w, float h);

    void open();

    void close();

    void draw(float *projMat, Shader *simpleShader, VertexBuff *vertexBuf);

    void draw(const DrawableData &drawableDate);

    unsigned int type() {return 76543;};

    bool init();

protected:
    virtual void doActionBefore();

    virtual void doActionAfter();

private:
    float w;
    float h;

    PhysicsObject *gate;
    std::stack<PhysicsObject *> frozenCircles;
    std::stack<GlassGameObject *> frozenGlasses;

    std::vector<CircleGameObject *> circles;
    std::vector<GlassGameObject *> glasses;
    ContainerGameObject *container;
    GlassGameObject *firstGlass;

    GlassPath glassPath;

    DrawService drawService;

    void addCircles(float initX, float initY, float direction, float r,
                    float distanceBetweenCircles, bool active, int numOfCircles);

    void checkFrozenGlasses();
};

#endif //NATIVE_ACTIVITY_PHYSICSSERVER_H
