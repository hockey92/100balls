#ifndef NATIVE_ACTIVITY_PHYSICSSERVER_H
#define NATIVE_ACTIVITY_PHYSICSSERVER_H

#include <vector>
#include <stack>
#include <pthread.h>
#include "PhysicsObject.h"
#include "BaseShape.h"
#include "PhysicsService.h"
#include "GlassGameObject.h"
#include "ContainerGameObject.h"

class GameService : public PhysicsService {
public:
    void open();

    void close();

    void reset();

    void draw(float currentTime);

    virtual void nextFrame(float dt);

    GameService(float w, float h, RendererFactory *rendererFactory);

    virtual ~GameService();

protected:
    virtual void doActionBefore();

    virtual void doActionAfter();

private:
    float w;
    float h;

    float r;

    int lastDrawn;

    float time;

    PhysicsObject *gate;
    std::stack<PhysicsObject *> frozenCircles;
    std::stack<GlassGameObject *> frozenGlasses;

    std::vector<CircleGameObject *> circles;
    std::vector<GlassGameObject *> glasses;
    ContainerGameObject *container;
    GlassGameObject *firstGlass;

    GlassPath *glassPath;

    Score score;

    FontRenderer* fontRenderer;

    void resetCircles(float initX, float initY, float direction, float r,
                      float distanceBetweenCircles, bool active, int numOfCircles,
                      int startCircleNumber);

    void checkFrozenGlasses();

    const int NUM_OF_GLASSES = 7;
    const int MAX_NUM_OF_ACTIVE_CIRCLES = 10;
};

#endif //NATIVE_ACTIVITY_PHYSICSSERVER_H
