#ifndef NATIVE_ACTIVITY_PHYSICSOBJECT_H
#define NATIVE_ACTIVITY_PHYSICSOBJECT_H

#include "Vec2.h"
#include "BaseShape.h"

class PhysicsObject {

public:
    PhysicsObject(BaseShape *shape, float invM) : angleVel(0), shape(shape), invM(invM),
                                                  active(true), deleted(false) { }

    ~PhysicsObject();

    void updateVel();

    virtual void update() { }

    virtual void updatePos();

    void applyGravity();

    Vec2 getVel() const { return vel; }

    float getAngleVel() const { return angleVel; }

    void setVel(const Vec2 &vel) { this->vel = vel; }

    void setAngleVel(float angleVel) { this->angleVel = angleVel; }

    float getInvM() const { return invM; }

    float getInvI() const { return invI; }

    void setInvM(float invM) { this->invM = invM; }

    void applyImpulse(const Vec2 &dVel) { vel += dVel; }

    BaseShape *getShape() const { return shape; }

    void draw(float *projection);

    bool isActive();

    bool isDeleted() { return deleted; }

    void setDeleted(bool deleted) { this->deleted = deleted; }

    void setActive(bool active) { this->active = active; }

    void calculateExtendedAABB();

private:
    Vec2 vel;
    float angleVel;
    BaseShape *shape;
    float invM;
    float invI;
    bool active;
    bool deleted;
};

#endif //NATIVE_ACTIVITY_PHYSICSOBJECT_H
