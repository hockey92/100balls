#ifndef NATIVE_ACTIVITY_GLASSSHAPE_H
#define NATIVE_ACTIVITY_GLASSSHAPE_H

#include "BaseShape.h"

class GlassShape : public BaseShape {

public:
    GlassShape();

    virtual int type() const { return 10; }

};

#endif //NATIVE_ACTIVITY_GLASSSHAPE_H
