#ifndef INC_100BALLS_COLLISIONINFO_H
#define INC_100BALLS_COLLISIONINFO_H

#include "PhysicsObject.h"
#include "Constraint.h"

class CollisionInfo {
public:
    CollisionInfo(PhysicsObject *o1, PhysicsObject *o2);

    virtual ~CollisionInfo();

    unsigned int getId() const;

    void addConstraint(Collision *c);

    bool isEmpty();

    void fix(float dt);

    void clear();

private:
    PhysicsObject *o1;
    PhysicsObject *o2;

    void swapIfNeeded();

    int _size;
    int _maxSize;

    bool swapped;

    Constraint *constraints[1000];

    friend bool operator<(const CollisionInfo &x, const CollisionInfo &y);
};

inline bool operator>(const CollisionInfo &x, const CollisionInfo &y) {
    return y < x;
}

inline bool operator>=(const CollisionInfo &x, const CollisionInfo &y) {
    return !(x < y);
}

inline bool operator<=(const CollisionInfo &x, const CollisionInfo &y) {
    return !(y < x);
}

inline bool operator==(const CollisionInfo &x, const CollisionInfo &y) {
    return !(x < y || y < x);
}

#endif //INC_100BALLS_BASEPHYSICSSERVICEKEY_H
