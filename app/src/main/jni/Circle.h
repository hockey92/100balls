#include "Segment.h"

#ifndef NATIVE_ACTIVITY_CIRCLE_H
#define NATIVE_ACTIVITY_CIRCLE_H

class Circle : public BaseShape {

public:
    Circle(float r);

    float getR() const {
        return r;
    }

    virtual int type() const { return 1; }

private:
    float r;
};

#endif //NATIVE_ACTIVITY_CIRCLE_H
