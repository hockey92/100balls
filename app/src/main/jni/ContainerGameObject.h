#ifndef NATIVE_ACTIVITY_CONTAINERGAMEOBJECT_H
#define NATIVE_ACTIVITY_CONTAINERGAMEOBJECT_H

#include "GameObject.h"
#include "GeometryRenderer.h"
#include "RendererFactory.h"

class ContainerGameObject : public GameObject {
public:
    ContainerGameObject(float invM, RendererFactory *rendererFactory);

    virtual ~ContainerGameObject();

    void draw();

    PhysicsObject *getGate();

private:
    PhysicsObject *gate;
    GeometryRenderer *renderer;
    static unsigned short openedGateIndices[];
    static unsigned short closedGateIndices[];
};

#endif //NATIVE_ACTIVITY_CONTAINERGAMEOBJECT_H
