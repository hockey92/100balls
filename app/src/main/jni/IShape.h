#ifndef TEAPOT_ISHAPE_H
#define TEAPOT_ISHAPE_H

#include "Vec2.h"

class IShape {
public:
    virtual Vec2 getCenter() const = 0;

    virtual void move(const Vec2 &coords) = 0;

//    virtual void rotate(float angle) = 0;

//    virtual int type() const { return 0; }

};

#endif //TEAPOT_ISHAPE_H
