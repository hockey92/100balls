#include "Circle.h"

Circle::Circle(float r) : BaseShape(), r(r) { }

float Circle::getR() const {
    return r;
}

int Circle::type() const {
    return 1;
}