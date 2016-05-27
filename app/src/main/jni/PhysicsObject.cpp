#include "Constants.h"
#include "PhysicsObject.h"

void PhysicsObject::updateVel() {

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
