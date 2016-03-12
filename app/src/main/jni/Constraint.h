#ifndef NATIVE_ACTIVITY_CONSTRAINT_H
#define NATIVE_ACTIVITY_CONSTRAINT_H

#include "PhysicsObject.h"
#include "Collision.h"

class Constraint {
public:
    Constraint(PhysicsObject* o1, PhysicsObject* o2, Collision* c);
    void fix();

private:
    PhysicsObject *o1;
    PhysicsObject *o2;
    Collision *c;
    float totalImpulse;

    float clamp(float impulse) {
        if (impulse < 0) {
            return 0;
        }
        return impulse;
    }
};

#endif //NATIVE_ACTIVITY_CONSTRAINT_H
