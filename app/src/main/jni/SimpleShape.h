#ifndef NATIVE_ACTIVITY_SIMPLESHAPE_H
#define NATIVE_ACTIVITY_SIMPLESHAPE_H

#include "BaseShape.h"
#include "Array.h"

class SimpleShape : public BaseShape {
public:
    virtual void getVertices(float *vertices);

    virtual int verticesSize();

protected:
    Array array;
};

#endif //NATIVE_ACTIVITY_SIMPLESHAPE_H
