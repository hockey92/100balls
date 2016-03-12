#ifndef NATIVE_ACTIVITY_COLLISIONFACTORY_H
#define NATIVE_ACTIVITY_COLLISIONFACTORY_H

#include "Segment.h"
#include "Circle.h"
#include "Collision.h"

class CollisionFactory {
public:
    static bool pointBelongsToSegment(Segment *s, const Vec2 &p);

    static Vec2 createDistance(const Vec2 &p, Segment *s, Vec2 &point);

    static Collision *createCollision(BaseShape *shape1, BaseShape *shape2);

private:
    static Collision *createCollision(Circle *circle1, Circle *circle2);

    static Collision *createCollision(Circle *circle, Segment *segment);
};

#endif //NATIVE_ACTIVITY_COLLISIONFACTORY_H