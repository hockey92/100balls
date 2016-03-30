#ifndef NATIVE_ACTIVITY_CIRCLEPHYSICSOBJECT_H
#define NATIVE_ACTIVITY_CIRCLEPHYSICSOBJECT_H

#include "PhysicsObject.h"
#include "Drawable.h"

class CirclePhysicsObject : public PhysicsObject, public Drawable {
public:
    CirclePhysicsObject(float r, float invM);

    virtual void updatePos();

    bool isInsideGlass();

    void setInsideGlass(bool insideGlass);

    void draw(const DrawableData &drawableDate);

    unsigned int type();

    Initializer *createInitializer();

private:
    bool insideGlass;

};

#endif //NATIVE_ACTIVITY_CIRCLEPHYSICSOBJECT_H
