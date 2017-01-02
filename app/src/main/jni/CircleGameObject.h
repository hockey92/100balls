#ifndef NATIVE_ACTIVITY_CIRCLEPHYSICSOBJECT_H
#define NATIVE_ACTIVITY_CIRCLEPHYSICSOBJECT_H

#include "PhysicsObject.h"
#include "RendererFactory.h"

class CircleGameObject : public PhysicsObject {
public:
    CircleGameObject(float r, float invM, float lowerBound, RendererFactory *rendererFactory);

    virtual void updatePos();

    bool isInsideGlass();

    void setInsideGlass(bool insideGlass);

    void draw();

    unsigned int type();

    void setColor(const Color &color);

private:
    bool insideGlass;
    Color color;
    float lowerBound;
    Renderer *renderer;
};

#endif //NATIVE_ACTIVITY_CIRCLEPHYSICSOBJECT_H
