#include "ImpulseFactory.h"
#include "Constants.h"

float ImpulseFactory::createImpulse(const PhysicsObject *o1, const PhysicsObject *o2,
                                    const Collision *c) {
    float vrn = Vec2::dot(o2->getVel() - o1->getVel(), c->getNormal());
    vrn -= c->getDist() / DT;
    return -1.f * vrn / (o1->getInvM() + o2->getInvM());
}
