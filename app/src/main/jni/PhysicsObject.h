#ifndef NATIVE_ACTIVITY_PHYSICSOBJECT_H
#define NATIVE_ACTIVITY_PHYSICSOBJECT_H

#include "Vec2.h"
#include "BaseShape.h"

class PhysicsObject {

public:
    PhysicsObject(BaseShape *shape, float invM) : angleVel(0), shape(shape),
                                                  invM(invM), active(true) { }

    ~PhysicsObject();

    void updateVel();

    void updatePos();

    virtual void update() { }

    void applyGravity();

    Vec2 getVel() const { return vel; }

    float getAngleVel() const { return angleVel; }

    void setVel(const Vec2 &vel) { this->vel = vel; }

    void setAngleVel(float angleVel) { this->angleVel = angleVel; }

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

    bool isActive() {
        return active;
    }

    void setActive(bool active) {
        this->active = active;
    }

    void calculateExtendedAABB();

private:
    static const float G = 10.f;

    Vec2 vel;
    float angleVel;
    BaseShape *shape;
    float invM;
    float invI;
    bool active;
};

#endif //NATIVE_ACTIVITY_PHYSICSOBJECT_H
