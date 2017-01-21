#ifndef NATIVE_ACTIVITY_GAMEOBJECT_H
#define NATIVE_ACTIVITY_GAMEOBJECT_H

#include "PhysicsObject.h"

enum {X, Y, ANGLE};

class GameObject : public PhysicsObject {
public:
    GameObject(BaseShape *shape, float invM);

    virtual void reset() { }

    virtual void draw(float delta) { }

    virtual void updatePos(float dt);

    static void incrementCycleNumber();

    static int getCycleNumber();

protected:
    float coordsToDraw[100][3]; // (x, y, angle)
    static int cycleNumber;
};

#endif //NATIVE_ACTIVITY_GAMEOBJECT_H
