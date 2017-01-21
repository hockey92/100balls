#ifndef NATIVE_ACTIVITY_GAMEOBJECT_H
#define NATIVE_ACTIVITY_GAMEOBJECT_H

#include "PhysicsObject.h"

class GameObject : public PhysicsObject {

public:
    GameObject(BaseShape *shape, float invM) : PhysicsObject(shape, invM) { }

    virtual void reset() { }

    virtual void draw() { }
};

#endif //NATIVE_ACTIVITY_GAMEOBJECT_H
