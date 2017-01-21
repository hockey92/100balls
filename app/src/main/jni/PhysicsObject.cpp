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

void PhysicsObject::updatePos(float dt) {
    if (shape) {
        shape->rotate(angleVel * dt);
        shape->move(vel * dt);
        shape->setAABB();
    }
}

void PhysicsObject::applyGravity(float dt) {
    if (invM > 0.f) {
        vel += Vec2(0.0f, -9.8f) * dt;
    }
}

PhysicsObject::~PhysicsObject() {
    if (shape) {
        delete shape;
    }
}

void PhysicsObject::calculateExtendedAABB(float dt) {
    shape->calculateExtendAABB(vel * dt);
}

bool PhysicsObject::isActive() {
    return active && !deleted;
}
