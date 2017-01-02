#ifndef TEAPOT_BASESHAPE_H
#define TEAPOT_BASESHAPE_H

#include <cstddef>
#include <Vec2.h>
#include <AABB.h>

class BaseShape {
public:
    BaseShape();

    virtual ~BaseShape();

    void move(const Vec2 &coords);

    void rotate(const float angle);

    Vec2 getCenter() const;

    void setCenter(const Vec2 &center);

    float getAngel() const;

    virtual int getSimpleShapesCount() const;

    virtual unsigned int type() const { return 0; }

    virtual BaseShape *getChildren(int i);

    void calculateExtendAABB(const Vec2 &moveVec);

    float getZ();

    AABB *getExtendedAABB();

    virtual void setInnerAABB();

    virtual void setAABB();

    virtual void getVertices(float *vertices) { }

    virtual int verticesSize() { return -1; }

protected:
    Vec2 center;
    int realChildCount;
    float angle;
    BaseShape **children;
    BaseShape *parent;
    AABB *aabb;
    AABB *extendedAABB;
    float z;

    virtual void innerRotate(float angle);

    void setAngle(float angle);
};

#endif //TEAPOT_BASESHAPE_H
