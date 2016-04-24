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
#include "ContainerGameObject.h"
#include "CallbackObject.h"

class GamePhysicsService : public BasePhysicsService, public CallbackObject, public Drawable {
public:
    GamePhysicsService(float w, float h, DrawService *drawService);

    void open();

    void close();

    void draw(const DrawableData &drawableDate);

    unsigned int type() { return 76543; };

    bool init();

    void reset();

protected:
    virtual void doActionBefore();

    virtual void doActionAfter();

private:
    float w;
    float h;

    float r;

    PhysicsObject *gate;
    std::stack<PhysicsObject *> frozenCircles;
    std::stack<GlassGameObject *> frozenGlasses;

    std::vector<CircleGameObject *> circles;
    std::vector<GlassGameObject *> glasses;
    ContainerGameObject *container;
    GlassGameObject *firstGlass;

    GlassPath glassPath;

    DrawService *drawService;

    void resetCircles(float initX, float initY, float direction, float r,
                      float distanceBetweenCircles, bool active, int numOfCircles,
                      int startCircleNumber);

    void checkFrozenGlasses();
};

#endif //NATIVE_ACTIVITY_PHYSICSSERVER_H
