#include "BaseShape.h"
#include "RendererPool.h"

#ifndef NATIVE_ACTIVITY_CONTAINER_H
#define NATIVE_ACTIVITY_CONTAINER_H

class Container : public BaseShape {

public:
    Container();// : BaseShape(RendererPool::getInstance()->getRenderer("container")) { }
};

#endif //NATIVE_ACTIVITY_CONTAINER_H
