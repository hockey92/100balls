#include "BaseShape.h"

#ifndef NATIVE_ACTIVITY_CONTAINER_H
#define NATIVE_ACTIVITY_CONTAINER_H

class Container : public BaseShape {

public:
    Container();

    virtual unsigned int type() const { return 9; }
};

#endif //NATIVE_ACTIVITY_CONTAINER_H
