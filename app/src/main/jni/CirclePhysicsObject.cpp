#include "CirclePhysicsObject.h"
#include "GameCoords.h"
#include "Circle.h"

CirclePhysicsObject::CirclePhysicsObject(float r, float invM) : PhysicsObject(new Circle(r),
                                                                              invM) { }

void CirclePhysicsObject::updatePos() {
    PhysicsObject::updatePos();
    if (getShape() != NULL) {
        float lowerBound = -GameCoords::getInstance()->getCoords(SCREEN_BORDERS)->getData()[HEIGHT];
        if (getShape()->getCenter().y() < lowerBound) {
            setDeleted(true);
        }
    }
}
