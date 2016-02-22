#include "Constants.h"
#include "PhysicsObject.h"

void PhysicsObject::updateVel() {

}

void PhysicsObject::updatePos() {
    if (shape) {
//        shape->rotate(angleVel * DT);
        shape->move(vel * DT);
    }
}

void PhysicsObject::applyGravity() {
    if (invM > 0.f) {
        vel += Vec2(0.f, -10.f) * DT;
    }
}

PhysicsObject::~PhysicsObject() {
    if (shape) {
        delete shape;
    }
}

void PhysicsObject::draw(float* projection) {
//    if (shape) {
        shape->draw(projection);
//    }
}

void PhysicsObject::calculateExtendedAABB() {
    shape->calculateExtendAABB(vel * DT);
}
