#include "Circle.h"
#include "RendererPool.h"

Circle::Circle(float r)
        : BaseShape(),
          r(r) {
    childCount = 1;

    _type = 1;

    children = new BaseShape *[1];
    children[0] = this;
}
