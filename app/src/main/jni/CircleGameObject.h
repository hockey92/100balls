#ifndef NATIVE_ACTIVITY_CIRCLEPHYSICSOBJECT_H
#define NATIVE_ACTIVITY_CIRCLEPHYSICSOBJECT_H

#include "PhysicsObject.h"
#include "Drawable.h"

class CircleGameObject : public PhysicsObject, public Drawable {
public:
    CircleGameObject(float r, float invM);

    virtual void updatePos();

    bool isInsideGlass();

    void setInsideGlass(bool insideGlass);

    void draw(const DrawableData &drawableDate);

    unsigned int type();

    Initializer *createInitializer();

    void setColor(const Color& color);

private:
    bool insideGlass;
    Color color;

};

#endif //NATIVE_ACTIVITY_CIRCLEPHYSICSOBJECT_H
