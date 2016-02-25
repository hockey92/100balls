#include "Gate.h"
#include "Circle.h"
#include "GameCoords.h"

Gate::Gate() {
    float *points = (GameCoords::getInstance()->getCoords(CONTAINER)->getData() + 6);
    init(Vec2(points[0], points[1]), Vec2(points[2], points[3]));
}
