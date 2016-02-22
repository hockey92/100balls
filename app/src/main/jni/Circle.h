#include "Segment.h"
#include "AABB.h"

#ifndef NATIVE_ACTIVITY_CIRCLE_H
#define NATIVE_ACTIVITY_CIRCLE_H

class Circle : public BaseShape {

public:
    Circle(float r);

    float getR() const;

    virtual int type() const;

    virtual void setAABB();

private:
    float r;
};

#endif //NATIVE_ACTIVITY_CIRCLE_H
