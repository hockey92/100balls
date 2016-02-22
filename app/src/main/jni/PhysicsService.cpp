#include "PhysicsService.h"
#include "Constraint.h"
#include "CollisionFactory.h"
#include "Container.h"
#include "GlassPhysicsObject.h"
#include "Gate.h"
#include "common.hpp"
#include <list>

PhysicsService::PhysicsService() {
    PhysicsObject *po = NULL;

    for (int i = 0; i < 100; i++) {
        po = new PhysicsObject(new Circle(0.06f), 0.1f);
        po->getShape()->move(Vec2((float) i * 0.001f, 0.15f * (float) i));
        physicsObjects.push_back(po);
    }
    physicsObjects.push_back(new PhysicsObject(new Container(), 0.f));

    GlassPhysicsObject *po1 = new GlassPhysicsObject();
    po1->getShape()->move(Vec2(2.1f, 0.f));
    physicsObjects.push_back(po1);

//    GlassPhysicsObject *parent = po1;
//    for (int i = 0; i < 6; i++) {
//        GlassPhysicsObject *po2 = new GlassPhysicsObject();
//        po2->getShape()->move(Vec2(-2.1f, 0.f));
//        physicsObjects.push_back(po2);
//
//        parent->setChildren(po2);
//        parent = po2;
//    }

    gate = new PhysicsObject(new Gate(), 0.f);
    physicsObjects.push_back(gate);
}

void PhysicsService::nextFrame() {

    for (int i = 0; i < physicsObjects.size(); i++) {
        physicsObjects[i]->update();
        physicsObjects[i]->applyGravity();
        physicsObjects[i]->calculateExtendedAABB();
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
                        constraints.push_back(
                                new Constraint(physicsObjects[i], physicsObjects[j], c)
                        );
                    }
                }
            }
        }
    }

//    LOGE("num of constraints %d", constraints.size());

    for (int i = 0; i < 10; i++) {
        for (std::list<Constraint *>::iterator iter = constraints.begin();
             iter != constraints.end(); ++iter) {
            (*iter)->fix();
        }
    }

    for (std::list<Constraint *>::iterator iter = constraints.begin();
         iter != constraints.end(); ++iter) {
        delete *iter;
    }

    for (int i = 0; i < physicsObjects.size(); i++) {
        physicsObjects[i]->updatePos();
    }
}

void PhysicsService::draw(float *projection) {
//    for (int i = 0; i < physicsObjects.size(); i++) {
//        physicsObjects[i]->draw(projection);
//    }
}

void PhysicsService::open() {
    gate->setActive(false);
}

void PhysicsService::close() {
    gate->setActive(true);
}
