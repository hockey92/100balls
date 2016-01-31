#ifndef NATIVE_ACTIVITY_PHYSICSOBJECT_H
#define NATIVE_ACTIVITY_PHYSICSOBJECT_H

#include "Vec2.h"
#include "IShape.h"
#include "BaseShape.h"

class PhysicsObject {

public:
    PhysicsObject(BaseShape *shape, float invM) : shape(shape), invM(invM) { }

    ~PhysicsObject();

    void updateVel();

    void updatePos();

    virtual void update() { }

    void applyGravity();

    Vec2 getVel() const { return vel; }

    void setVel(const Vec2 &vel) { this->vel = vel; }

    float getInvM() const { return invM; }

    float getInvI() const { return invI; }

    void setInvM(float invM) {
        this->invM = invM;
    }

    void applyImpulse(const Vec2 &dVel) {
        vel += dVel;
    }

    BaseShape *getShape() const { return shape; }

    void draw(float *projection);

private:
    static const float G = 10.f;

    Vec2 vel;
    BaseShape *shape;
    float invM;
    float invI;
};

#endif //NATIVE_ACTIVITY_PHYSICSOBJECT_H
