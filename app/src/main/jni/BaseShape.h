#ifndef TEAPOT_BASESHAPE_H
#define TEAPOT_BASESHAPE_H

#include "IShape.h"
#include <pthread.h>

class BaseShape : public IShape {

public:
    BaseShape() : _type(0),
                  parent(NULL),
                  angle(0.f) { }

    void move(const Vec2 &coords);

    void rotate(const float angle);

    Vec2 getCenter() const;

    float getAngel() const;

    void draw(float *projection);

    virtual int getChildCount() const {
        return childCount;
    }

    virtual BaseShape *getChildren(int i);

    virtual int type() const { return 0; }

protected:
    Vec2 center;
    int childCount;
    int _type;
    float angle;
    BaseShape **children;
    BaseShape *parent;

    virtual void innerRotate(float angle);
};

#endif //TEAPOT_BASESHAPE_H
