#include "Container.h"
#include "Segment.h"
#include "GameCoords.h"

Container::Container() : BaseShape() {
    float *points = GameCoords::getInstance()->getCoords(CONTAINER)->getData();
    realChildCount = 6;
    children = new BaseShape *[6];
    for (int i = 0; i < realChildCount + 1; i++) {
        if (i == 3) {
            continue;
        }
        children[i > 3 ? i - 1 : i] = new Segment(
                this,
                Vec2(points[i * 2], points[i * 2 + 1]),
                Vec2(points[i * 2 + 2], points[i * 2 + 3])
        );
    }
}
