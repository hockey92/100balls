#ifndef TEAPOT_SEGMENT_H
#define TEAPOT_SEGMENT_H

#include "Vec2.h"
#include "BaseShape.h"

#endif //TEAPOT_SEGMENT_H

class Segment : public BaseShape {

public:
    Segment() { }

    Segment(Vec2 p1, Vec2 p2);

    Segment(BaseShape *parent, Vec2 p1, Vec2 p2);

    Vec2 get(int i) const;

    Vec2 getPoint(int i) const;

    virtual int type() const { return 2; }

    virtual void innerRotate(float angle);

    virtual void setInnerAABB();

protected:
    void init(Vec2 p1, Vec2 p2);

private:
    Vec2 points[2];
    Vec2 initPoints[2];
};
