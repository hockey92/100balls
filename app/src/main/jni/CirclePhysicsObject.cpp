#include "CirclePhysicsObject.h"
#include "GameCoords.h"
#include "Circle.h"

CirclePhysicsObject::CirclePhysicsObject(float r, float invM) : PhysicsObject(new Circle(r), invM),
                                                                insideGlass(false) { }

void CirclePhysicsObject::updatePos() {
    PhysicsObject::updatePos();
    if (getShape() != NULL) {
        float lowerBound = -GameCoords::getInstance()->getCoords(SCREEN_BORDERS)->getData()[HEIGHT];
        if (getShape()->getCenter().y() < lowerBound) {
            setDeleted(true);
        }
    }
}

bool CirclePhysicsObject::isInsideGlass() {
    return insideGlass;
}

void CirclePhysicsObject::setInsideGlass(bool insideGlass) {
    this->insideGlass = insideGlass;
}
