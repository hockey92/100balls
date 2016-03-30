#include "Gate.h"
#include "GameCoords.h"

Gate::Gate() {
    float *points = (GameCoords::getInstance()->getCoords(CONTAINER)->getData() + 10);
    init(Vec2(points[0], points[1]), Vec2(points[6], points[7]));
}
