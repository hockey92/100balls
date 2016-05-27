#include "BasePhysicsService.h"
#include "Constraint.h"
#include "CollisionFactory.h"
#include <list>

BasePhysicsService::BasePhysicsService() : status(STOPPED) { }

void BasePhysicsService::nextFrame() {

    if (status != PROCESSING) {
        return;
    }

    doActionBefore();
    for (int i = 0; i < physicsObjects.size(); i++) {
        PhysicsObject *po = physicsObjects[i];
        if (!po->isActive()) {
            continue;
        }
        po->update();
        po->applyGravity();
        po->calculateExtendedAABB();
    }

    std::list<Constraint *> constraints;
    for (int i = 0; i < physicsObjects.size(); i++) {
        PhysicsObject *po1 = physicsObjects[i];
        if (!po1->isActive()) {
            continue;
        }
        for (int j = i + 1; j < physicsObjects.size(); j++) {
            PhysicsObject *po2 = physicsObjects[j];
            if (!po2->isActive()) {
                continue;
            }
            for (int k = 0; k < po1->getShape()->getSimpleShapesCount(); k++) {
                for (int l = 0; l < po2->getShape()->getSimpleShapesCount(); l++) {
                    BaseShape *shape1 = po1->getShape()->getChildren(k);
                    BaseShape *shape2 = po2->getShape()->getChildren(l);
                    if (!AABB::isIntersect(shape1->getExtendedAABB(), shape2->getExtendedAABB())) {
                        continue;
                    }
                    Collision *c = CollisionFactory::createCollision(shape1, shape2);
                    if (c != NULL) {
                        constraints.push_back(new Constraint(physicsObjects[i], physicsObjects[j], c));
                    }
                }
            }
        }
    }

//    LOGE("num of constraints %d", constraints.size());

    for (int i = 0; i < 10; i++) {
        for (std::list<Constraint *>::iterator iter = constraints.begin(); iter != constraints.end(); ++iter) {
            (*iter)->fix();
        }
    }

    for (std::list<Constraint *>::iterator iterator = constraints.begin(); iterator != constraints.end(); ++iterator) {
        delete *iterator;
    }

    for (int i = 0; i < physicsObjects.size(); i++) {
        PhysicsObject *po = physicsObjects[i];
        if (!po->isActive()) {
            continue;
        }
        po->updatePos();
    }

    doActionAfter();
}

int BasePhysicsService::getStatus() {
    return status;
}

void BasePhysicsService::setStatus(int status) {
    this->status = status;
}

BasePhysicsService::~BasePhysicsService() {
    for (int i = 0; i < physicsObjects.size(); i++) {
        delete physicsObjects[i];
    }
}
