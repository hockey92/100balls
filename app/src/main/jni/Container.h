#ifndef NATIVE_ACTIVITY_CONTAINER_H
#define NATIVE_ACTIVITY_CONTAINER_H

#include "BaseShape.h"
#include "ArrayWrapper.h"
#include "SimpleShape.h"

class Container : public SimpleShape {

public:
    Container();

    virtual unsigned int type() const { return 9; }
};

#endif //NATIVE_ACTIVITY_CONTAINER_H
