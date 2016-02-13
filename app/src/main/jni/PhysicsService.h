#ifndef NATIVE_ACTIVITY_PHYSICSSERVER_H
#define NATIVE_ACTIVITY_PHYSICSSERVER_H

#include <vector>
#include <pthread.h>
#include "PhysicsObject.h"
#include "BaseShape.h"
#include "TextureRenderer.h"
#include "RendererPool.h"

class PhysicsService {
public:
    PhysicsService() {
        textureRenderer = RendererPool::getInstance()->getRenderer("circle");
    }

    void nextFrame();

    void draw(float *projection);

    void open();

    void close();

private:
    std::vector<PhysicsObject*> physicsObjects;
    PhysicsObject* gate;
    Renderer* textureRenderer;

//    pthread_t threadId;
//
//    static void *threadFunc(void *ptr);
//
//    void run();
};

#endif //NATIVE_ACTIVITY_PHYSICSSERVER_H
