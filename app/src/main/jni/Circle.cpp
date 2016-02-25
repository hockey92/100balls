#include "Circle.h"
#include "GameCoords.h"

Circle::Circle(float r) : BaseShape() {
    this->r = GameCoords::getInstance()->getCoords(BALL)->getData()[0];
    setAABB();
}

float Circle::getR() const {
    return r;
}

int Circle::type() const {
    return 1;
}

void Circle::setAABB() {
    float x = getCenter().x(), y = getCenter().y();
    float right = x + r;
    float up = y + r;
    float left = x - r;
    float down = y - r;

    if (aabb == NULL) {
        aabb = new AABB(left, down, right, up);
    } else {
        aabb->set(left, down, right, up);
    }
}
