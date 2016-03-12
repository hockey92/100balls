#include "Container.h"
#include "Segment.h"
#include "GameCoords.h"

Container::Container() : BaseShape() {
    float *points = GameCoords::getInstance()->getCoords(CONTAINER)->getData();
    realChildCount = GameCoords::getInstance()->getCoords(CONTAINER)->getSize() - 4;
    children = new BaseShape *[realChildCount];
    int indices[] = {0, 1, 2, 3, 4, 6, 7, 9, 10, 11, 12, 13};
    for (int i = 0; i < realChildCount + 1; i++) {
        if (i == 5) {
            continue;
        }
        children[i > 5 ? i - 1 : i] = new Segment(
                this,
                Vec2(points[indices[i] * 2], points[indices[i] * 2 + 1]),
                Vec2(points[indices[i + 1] * 2], points[indices[i + 1] * 2 + 1])
        );
    }
}
