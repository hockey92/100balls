#include "CollisionInfo.h"
#include "IdUtils.h"

CollisionInfo::CollisionInfo(PhysicsObject *o1, PhysicsObject *o2) {
    this->o1 = o1;
    this->o2 = o2;

    swapIfNeeded();

    _size = 0;
    _maxSize = 0;
}

void CollisionInfo::swapIfNeeded() {
    swapped = false;
    if (o1->getId() > o2->getId()) {
        PhysicsObject *temp = o1;
        o1 = o2;
        o2 = temp;
        swapped = true;
    }
}

unsigned int CollisionInfo::getId() const {
    return IdUtils::createKey(o1->getId(), o2->getId());
}

bool operator<(const CollisionInfo &x, const CollisionInfo &y) {
    return x.getId() < y.getId();
}

void CollisionInfo::addConstraint(Collision *c) {
    if (_size == _maxSize) {
        constraints[_size] = swapped ? new Constraint(o2, o1, c) : new Constraint(o1, o2, c);
        _maxSize++;
    } else {
        if (swapped) {
            constraints[_size]->set(o2, o1, c);
        } else {
            constraints[_size]->set(o1, o2, c);
        }
    }
    _size++;
}

CollisionInfo::~CollisionInfo() {

}

bool CollisionInfo::isEmpty() {
    return _size <= 0;
}

void CollisionInfo::fix(float dt) {
    for (int i = 0; i < _size; i++) {
        constraints[i]->fix(dt);
    }
}

void CollisionInfo::clear() {
    _size = 0;
}
