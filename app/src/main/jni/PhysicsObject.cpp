#include "Constants.h"
#include "PhysicsObject.h"

unsigned int PhysicsObject::idCounter = 0;

Mutex PhysicsObject::idMutex;

PhysicsObject::PhysicsObject(BaseShape *shape, float invM) : angleVel(0),
                                                             shape(shape),
                                                             invM(invM),
                                                             active(true),
                                                             deleted(false),
                                                             visible(true) {
    idMutex.lock();
    id = idCounter++;
    idMutex.unlock();
}

void PhysicsObject::updatePos() {
    if (shape) {
        shape->rotate(angleVel * DT);
        shape->move(vel * DT);
        shape->setAABB();
    }
}

void PhysicsObject::applyGravity() {
    if (invM > 0.f) {
        vel += Vec2(0.0f, -9.8f) * DT;
    }
}

PhysicsObject::~PhysicsObject() {
    if (shape) {
        delete shape;
    }
}

void PhysicsObject::calculateExtendedAABB() {
    shape->calculateExtendAABB(vel * DT);
}

bool PhysicsObject::isActive() {
    return active && !deleted;
}
