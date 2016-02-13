#include "CollisionFactory.h"
#include "Line.h"

bool CollisionFactory::pointBelongsToSegment(Segment *s, const Vec2 &p) {
    float d = 0.001f;
    for (int i = 0; i < 2; i++) {
        float a1 = s->get(0).get(i);
        float a2 = s->get(1).get(i);
        float a = p.get(i);

        if (!(a1 - d <= a && a <= a2 + d) && !(a2 - d <= a && a <= a1 + d)) {
            return false;
        }
    }
    return true;
}

Vec2 CollisionFactory::createDistance(const Vec2 &p, Segment *s, Vec2 &point) {
    Line line = Line(s->get(0), s->get(1));
    Line pLine = Line(p, p + line.getNormal());
    Vec2 mutualPoint = Vec2(Line::getMutualPoint(line, pLine));
    if (pointBelongsToSegment(s, mutualPoint)) {
        point = mutualPoint;
        return (mutualPoint - p);
    } else {
        Vec2 a;
        float aLen = 0;
        int pointNum = 0;
        for (int i = 0; i < 2; i++) {
            Vec2 d = s->get(i) - p;
            float len = d.len();
            if (i == 0 || len < aLen) {
                a = d;
                aLen = len;
                pointNum = i;
            }
        }
        point = s->get(pointNum);
        return a;
    }
}

Collision *CollisionFactory::createCollision(BaseShape *shape1, BaseShape *shape2) {
    if (shape1->type() == 1 && shape2->type() == 1) {
        return createCollision((Circle *) shape1, (Circle *) shape2);
    } else if (shape1->type() == 1 && shape2->type() == 2) {
        return createCollision((Circle *) shape1, (Segment *) shape2);
    } else if (shape1->type() == 2 && shape2->type() == 1) {
        Collision* result = createCollision((Circle *) shape2, (Segment *) shape1);
        result->swap();
        return result;
    }
    return NULL;
}

Collision *CollisionFactory::createCollision(Circle *c1, Circle *c2) {
    Vec2 v = c2->getCenter() - c1->getCenter();
    float d = v.len();
    float r = c1->getR() + c2->getR();
    Vec2 n = v * (1.f / d);
    Vec2 r1 = n * c1->getR();
    Vec2 r2 = -c2->getR() * n;
    return new Collision(n, r1, r2, r - d);
}

Collision *CollisionFactory::createCollision(Circle *c, Segment *s) {
    Vec2 mutualPoint;
    Vec2 v1 = createDistance(c->getCenter(), s, mutualPoint);
    float len = v1.len();
    Vec2 n = v1 * (1.f / len);
    Vec2 r1 = n * c->getR();
    Vec2 r2 = mutualPoint - s->getCenter();
    float penetration = c->getR() - len;
    return new Collision(n, r1, r2, penetration);
}
