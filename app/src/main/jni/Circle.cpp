#include "Circle.h"
#include "RendererPool.h"

Circle::Circle(float r)
        : BaseShape(RendererPool::getInstance()->getRenderer("circle")),
          r(r) {
    childCount = 1;

    _type = 1;

    children = new BaseShape *[1];
    children[0] = this;
}
