#ifndef NATIVE_ACTIVITY_CONTAINERGAMEOBJECT_H
#define NATIVE_ACTIVITY_CONTAINERGAMEOBJECT_H

#include "GameObject.h"

class ContainerGameObject : public GameObject {
public:
    ContainerGameObject(BaseShape *shape, float invM);

    virtual ~ContainerGameObject();

    void draw(const DrawableData &drawableDate);

    unsigned int type();

    PhysicsObject *getGate();

private:
    PhysicsObject *gate;
};

#endif //NATIVE_ACTIVITY_CONTAINERGAMEOBJECT_H
