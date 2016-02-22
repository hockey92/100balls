#ifndef TEAPOT_BASESHAPE_H
#define TEAPOT_BASESHAPE_H

#include <cstddef>
#include "Vec2.h"
#include "AABB.h"

class BaseShape {
public:
    BaseShape();

    virtual ~BaseShape();

    void move(const Vec2 &coords);

    void rotate(const float angle);

    Vec2 getCenter() const;

    float getAngel() const;

    void draw(float *projection);

    virtual int getSimpleShapesCount() const;

    virtual int type() const { return 0; }

    virtual BaseShape *getChildren(int i);

    void calculateExtendAABB(const Vec2 &moveVec);

    AABB *getExtendedAABB();

protected:
    Vec2 center;
    int realChildCount;
    float angle;
    BaseShape **children;
    BaseShape *parent;
    AABB *aabb;
    AABB *extendedAABB;

    virtual void innerRotate(float angle);

    virtual void setAABB();
};

#endif //TEAPOT_BASESHAPE_H
