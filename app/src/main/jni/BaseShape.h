#ifndef TEAPOT_BASESHAPE_H
#define TEAPOT_BASESHAPE_H

#include <cstddef>
#include "Vec2.h"

class BaseShape {

public:
    BaseShape() : realChildCount(0), parent(NULL), angle(0.f) { }

    void move(const Vec2 &coords);

    void rotate(const float angle);

    Vec2 getCenter() const;

    float getAngel() const;

    void draw(float *projection);

    virtual int getChildCount() const;

    virtual int type() const { return 0; }

    virtual BaseShape *getChildren(int i);

protected:
    Vec2 center;
    int realChildCount;
    float angle;
    BaseShape **children;
    BaseShape *parent;

    virtual void innerRotate(float angle);
};

#endif //TEAPOT_BASESHAPE_H
