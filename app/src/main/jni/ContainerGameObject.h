#ifndef NATIVE_ACTIVITY_CONTAINERGAMEOBJECT_H
#define NATIVE_ACTIVITY_CONTAINERGAMEOBJECT_H

#include "GameObject.h"

class ContainerGameObject : public GameObject {
public:
    ContainerGameObject(BaseShape *shape, float invM) : GameObject(shape, invM),
                                                        gate(NULL) { }

    void draw(const DrawableData &drawableDate);

    unsigned int type();

    void setGate(PhysicsObject *gate);

private:
    PhysicsObject *gate;
};

#endif //NATIVE_ACTIVITY_CONTAINERGAMEOBJECT_H
