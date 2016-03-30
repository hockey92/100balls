#ifndef NATIVE_ACTIVITY_GLASSSHAPE_H
#define NATIVE_ACTIVITY_GLASSSHAPE_H

#include "BaseShape.h"

class GlassShape : public BaseShape {

public:
    GlassShape();

    virtual unsigned int type() const;

private:
    static float *vertices;
};

#endif //NATIVE_ACTIVITY_GLASSSHAPE_H
