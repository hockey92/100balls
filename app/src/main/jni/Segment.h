#ifndef TEAPOT_SEGMENT_H
#define TEAPOT_SEGMENT_H

#include "Vec2.h"
#include "BaseShape.h"

class Segment : public BaseShape {

public:
    Segment(Vec2 p1, Vec2 p2);

    Segment(BaseShape* parent, Vec2 p1, Vec2 p2);

    Vec2 get(int i) const {
        if (!parent) {
            return points[i];
        } else {
            return parent->getCenter() + points[i];
        }
    }

protected:

//    virtual int type() const {
//        return 2;
//    }

private:
    Vec2 points[2];
};

#endif //TEAPOT_SEGMENT_H
