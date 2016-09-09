#include "BasePhysicsService.h"
#include "CollisionFactory.h"
#include "common.h"
#include "IdUtils.h"

BasePhysicsService::BasePhysicsService() : status(STOPPED) {
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 10000000; i++) {
        collisionInfos[i] = NULL;
    }
}

void BasePhysicsService::nextFrame() {

//    double beforeTime = now();

    std::vector<CollisionInfo *> collisionInfos1;

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

            if (!collisionInfo->isCalculateNewCollision()) {
                if (!collisionInfo->isEmpty()) {
                    collisionInfos1.push_back(collisionInfo);
                }
            } else {
                collisionInfo->calculateDiff();
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
                    collisionInfos1.push_back(collisionInfo);
                }
            }
        }
    }

    LOGE("new collisions count %d", newCollisionsCount);

//    for (int i = 0; i < collisionInfos1.size(); i++) {
//        collisionInfos1[i]->reset();
//    }


    for (int iteration = 0; iteration < 10; iteration++) {
        for (int i = 0; i < collisionInfos1.size(); i++) {
            collisionInfos1[i]->fix();
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
        po->updatePos();
    }
//    pthread_mutex_unlock(&mutex);

    doActionAfter();

//    double afterTime = now();
//    unsigned int delay = 30 - (unsigned int) (afterTime - beforeTime);
//    delay = delay < 2 ? 2 : delay;
//    LOGE("delay %d", delay);
//    usleep(delay * 1000);
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

void BasePhysicsService::innerRun() {
    double time = now();
    while (!isStop) {
        double currentTime = now();
        LOGE("timeDiff %f", currentTime - time);
        time = currentTime;
        double timeBefore = now();
        nextFrame();
        double timeAfter = now();

        int delay = 16 - (int) (timeAfter - timeBefore);
        delay = delay < 2 ? 2 : delay;
        usleep((unsigned int) delay * 1000);
    }
}

void BasePhysicsService::addPhysicsObjects(PhysicsObject *physicsObject) {
    physicsObjects.push_back(physicsObject);
}
