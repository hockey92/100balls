#ifndef NATIVE_ACTIVITY_GAMEOBJECT_H
#define NATIVE_ACTIVITY_GAMEOBJECT_H

#include "Drawable.h"
#include "PhysicsObject.h"

class GameObject : public PhysicsObject, public Drawable {

public:
    GameObject(BaseShape *shape, float invM) : PhysicsObject(shape, invM) { }

    virtual Initializer *createInitializer();
};

#endif //NATIVE_ACTIVITY_GAMEOBJECT_H
