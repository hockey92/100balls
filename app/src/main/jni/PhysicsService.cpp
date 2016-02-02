#include "PhysicsService.h"
#include "Constraint.h"
#include "CollisionFactory.h"
#include "Container.h"
#include "GlassPhysicsObject.h"
#include "Gate.h"
#include <list>

PhysicsService::PhysicsService() {
//    pthread_create(&threadId, NULL, threadFunc, this);

    PhysicsObject *po = NULL;

    for (int i = 0; i < 40; i++) {
        po = new PhysicsObject(new Circle(0.06f), 0.1f);
        po->getShape()->move(Vec2((float) i * 0.001f, 0.15f * (float) i));
        physicsObjects.push_back(po);
    }
    physicsObjects.push_back(new PhysicsObject(new Container(), 0.f));

    po = new GlassPhysicsObject();
    po->getShape()->move(Vec2(2.1f, 0.f));
    physicsObjects.push_back(po);

    po = new GlassPhysicsObject();
    po->getShape()->move(Vec2(-2.1f, 0.f));
    physicsObjects.push_back(po);

    po = new GlassPhysicsObject();
    po->getShape()->move(Vec2(-2.1f, 2.f));
    physicsObjects.push_back(po);

    po = new GlassPhysicsObject();
    po->getShape()->move(Vec2(2.1f, 2.f));
    physicsObjects.push_back(po);

    gate = new PhysicsObject(new Gate(), 0.f);
    physicsObjects.push_back(gate);
}

//void *PhysicsService::threadFunc(void *ptr) {
//    ((PhysicsService *) ptr)->run();
//}
//
//void PhysicsService::run() {
//
//}

void PhysicsService::nextFrame() {

    for (int i = 0; i < physicsObjects.size(); i++) {
//        physicsObjects[i]->updateVel();
        physicsObjects[i]->update();
        physicsObjects[i]->applyGravity();
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
            for (int k = 0; k < po1->getShape()->getChildCount(); k++) {
                for (int l = 0; l < po2->getShape()->getChildCount(); l++) {
                    Collision *c = CollisionFactory::createCollision(
                            po1->getShape()->getChildren(k),
                            po2->getShape()->getChildren(l)
                    );
                    if (c != NULL) {
                        constraints.push_back(
                                new Constraint(physicsObjects[i], physicsObjects[j], c)
                        );
                    }
                }
            }
        }
    }

    for (int i = 0; i < 5; i++) {
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
    for (int i = 0; i < physicsObjects.size(); i++) {
        physicsObjects[i]->draw(projection);
    }
}

void PhysicsService::open() {
    gate->setActive(false);
}

void PhysicsService::close() {
    gate->setActive(true);
}
