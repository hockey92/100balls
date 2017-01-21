#include "PhysicsService.h"
#include "CollisionFactory.h"
#include "common.h"
#include "IdUtils.h"

PhysicsService::PhysicsService() : status(STOPPED) {
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 10000000; i++) {
        collisionInfos[i] = NULL;
    }

//    start();
}

void PhysicsService::nextFrame(float dt) {

    if (dt == 0) {
        return;
    }

    double beforeTime = now();

    std::vector<CollisionInfo *> collisionInfosToFix;

    doActionBefore();
    for (int i = 0; i < physicsObjects.size(); i++) {
        PhysicsObject *po = physicsObjects[i];
        if (!po->isActive()) {
            continue;
        }
        po->update(dt);
        po->applyGravity(dt);
        po->calculateExtendedAABB(dt);
    }

    int newCollisionsCount = 0;

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
            int collisionId = IdUtils::createKey(po1->getId(), po2->getId());

            CollisionInfo *collisionInfo = collisionInfos[collisionId];
            if (collisionInfo == NULL) {
                collisionInfo = collisionInfos[collisionId] = new CollisionInfo(po1, po2);
            }

            collisionInfo->clear();
            for (int k = 0; k < po1->getShape()->getSimpleShapesCount(); k++) {
                for (int l = 0; l < po2->getShape()->getSimpleShapesCount(); l++) {
                    BaseShape *shape1 = po1->getShape()->getChildren(k);
                    BaseShape *shape2 = po2->getShape()->getChildren(l);
                    if (!AABB::isIntersect(shape1->getExtendedAABB(),
                                           shape2->getExtendedAABB())) {
                        continue;
                    }
                    newCollisionsCount++;
                    Collision *c = CollisionFactory::createCollision(shape1, shape2);
                    if (c != NULL) {
                        collisionInfo->addConstraint(c);
                    }
                }
            }
            if (!collisionInfo->isEmpty()) {
                collisionInfosToFix.push_back(collisionInfo);
            }
        }
    }

    LOGE("new collisions count %d", newCollisionsCount);

    for (int iteration = 0; iteration < 10; iteration++) {
        for (int i = 0; i < collisionInfosToFix.size(); i++) {
            collisionInfosToFix[i]->fix(dt);
        }
    }

//    LOGE("num of constraints %d, vector size %d", realConstraintSize, constraints.size());

//    bool contact = false;
//    for (int iteration = 0; iteration < 10; iteration++) {
//        for (int constraintNumber = 0; constraintNumber < realConstraintSize; constraintNumber++) {
//            if (constraints[constraintNumber].fix()) {
//                contact = true;
//            }
//        }
//    }
//    if (contact) {
//        audioService.push();
//    }

//    pthread_mutex_lock(&mutex);
    for (int i = 0; i < physicsObjects.size(); i++) {
        PhysicsObject *po = physicsObjects[i];
        if (!po->isActive()) {
            continue;
        }
        po->updatePos(dt);
    }
//    pthread_mutex_unlock(&mutex);

    doActionAfter();

//    double afterTime = now();
//    unsigned int delay = 30 - (unsigned int) (afterTime - beforeTime);
//    delay = delay < 2 ? 2 : delay;
//    LOGE("delay %d", delay);
//    usleep(delay * 1000);

    LOGE("collision time %f", now() - beforeTime);
}

int PhysicsService::getStatus() {
    return status;
}

void PhysicsService::setStatus(int status) {
    this->status = status;
}

PhysicsService::~PhysicsService() {
    for (int i = 0; i < physicsObjects.size(); i++) {
        delete physicsObjects[i];
    }
}

void PhysicsService::innerRun() {
    double prevTime = now() / 1000.0;
    while (!isStop) {
        double currentTime = now() / 1000.0;
//        prevTime = currentTime;
//        double timeBefore = now();


        if (currentTime - prevTime >= 0.016) {
            nextFrame((float) (currentTime - prevTime));
            LOGE("timeDiff %f", currentTime - prevTime);
            prevTime = currentTime;
        }


//        double timeAfter = now();

//        int delay = 8 - (int) (currentTime - prevTime) * 1000;
//        delay = delay < 2 ? 2 : delay;
//        usleep((unsigned int) delay * 1000);
    }
}

void PhysicsService::addPhysicsObjects(PhysicsObject *physicsObject) {
    physicsObjects.push_back(physicsObject);
}
