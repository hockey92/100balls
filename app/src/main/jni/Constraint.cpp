#include "Constraint.h"
#include "ImpulseFactory.h"

Constraint::Constraint(PhysicsObject *o1, PhysicsObject *o2, Collision *c) {
    this->o1 = o1;
    this->o2 = o2;
    this->c = c;

    totalImpulse = 0;
}

void Constraint::fix() {
    float j = ImpulseFactory::createImpulse(o1, o2, c);
    float oldImpulse = totalImpulse;
    totalImpulse = clamp(oldImpulse + j);
    j = totalImpulse - oldImpulse;
    o1->applyImpulse(-j * o1->getInvM() * c->getNormal());
    o2->applyImpulse(j * o2->getInvM() * c->getNormal());
}
