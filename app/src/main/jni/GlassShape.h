#ifndef NATIVE_ACTIVITY_GLASSSHAPE_H
#define NATIVE_ACTIVITY_GLASSSHAPE_H

#include "BaseShape.h"
#include "Array.h"
#include "SimpleShape.h"

class GlassShape : public SimpleShape {

public:
    GlassShape();

    virtual unsigned int type() const;
};

#endif //NATIVE_ACTIVITY_GLASSSHAPE_H
