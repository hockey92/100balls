#ifndef NATIVE_ACTIVITY_SIMPLESHAPE_H
#define NATIVE_ACTIVITY_SIMPLESHAPE_H

#include "BaseShape.h"
#include "ArrayWrapper.h"

class SimpleShape : public BaseShape {
public:
    virtual void getVertices(float *vertices);

    virtual int verticesSize();

protected:
    ArrayWrapper array;
};

#endif //NATIVE_ACTIVITY_SIMPLESHAPE_H
