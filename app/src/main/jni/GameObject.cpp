#include "GameObject.h"

int GameObject::cycleNumber = 1;

void GameObject::updatePos(float dt) {
    PhysicsObject::updatePos(dt);

    Vec2 center = getShape()->getCenter();

    coordsToDraw[cycleNumber][X] = center.x();
    coordsToDraw[cycleNumber][Y] = center.y();
    coordsToDraw[cycleNumber][ANGLE] = getShape()->getAngel();
}

void GameObject::incrementCycleNumber() {
    cycleNumber = (cycleNumber + 1) % 100;
}

int GameObject::getCycleNumber() {
    return cycleNumber;
}

GameObject::GameObject(BaseShape *shape, float invM) : PhysicsObject(shape, invM) {
    coordsToDraw[0][X] = 0;
    coordsToDraw[0][Y] = 0;
    coordsToDraw[0][ANGLE] = 0;
}