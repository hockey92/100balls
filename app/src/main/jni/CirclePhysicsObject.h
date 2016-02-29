#ifndef NATIVE_ACTIVITY_CIRCLEPHYSICSOBJECT_H
#define NATIVE_ACTIVITY_CIRCLEPHYSICSOBJECT_H

#include "PhysicsObject.h"

class CirclePhysicsObject : public PhysicsObject {
public:
    CirclePhysicsObject(float r, float invM);

    virtual void updatePos();

    bool isInsideGlass();

    void setInsideGlass(bool insideGlass);

private:
    bool insideGlass;

};

#endif //NATIVE_ACTIVITY_CIRCLEPHYSICSOBJECT_H
