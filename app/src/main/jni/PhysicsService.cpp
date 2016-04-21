#include "PhysicsService.h"
#include "Container.h"
#include "common.hpp"
#include "ScoreService.h"

PhysicsService::PhysicsService(float w, float h, DrawService *drawService) : w(w), h(h),
                                                                             drawService(
                                                                                     drawService) {

    r = 0.0355f;

    container = new ContainerGameObject(new Container(), 0.f);

    for (int i = 0; i < 100; i++) {
        CircleGameObject *circleGO = new CircleGameObject(r, 1.0f);
        drawService->add(circleGO);
        physicsObjects.push_back(circleGO);
        circles.push_back(circleGO);
    }

    drawService->add(container);
    physicsObjects.push_back(container);
    gate = container->getGate();
    physicsObjects.push_back(gate);

    for (int i = 0; i < 7; i++) {
        GlassGameObject *glassGO = new GlassGameObject(&glassPath);
        physicsObjects.push_back(glassGO);
        glasses.push_back(glassGO);
        drawService->add(glassGO);
    }

    reset();
}

void PhysicsService::resetCircles(float initX, float initY, float direction, float r,
                                  float distanceBetweenCircles, bool active, int numOfCircles,
                                  int startCircleNumber) {
    for (int i = 0; i < numOfCircles; i++) {
        CircleGameObject *go = circles[startCircleNumber + i];
        float x = initX + direction * (i % 5) * (2.0f * r + distanceBetweenCircles);
        float y = initY - (i / 5) * (2.0f * r + distanceBetweenCircles);
        if (!active) {
            frozenCircles.push(go);
        }
        go->setDeleted(false);
        go->setActive(active);
        go->setVisible(true);
        go->setVel(Vec2());
        go->getShape()->setCenter(Vec2(x, y));
    }
}

void PhysicsService::open() {
    if (getStatus() == PROCESSING) {
        gate->setActive(false);
    }
}

void PhysicsService::close() {
    if (getStatus() == PROCESSING) {
        gate->setActive(true);
    }
}

void PhysicsService::doActionBefore() {

}

void PhysicsService::doActionAfter() {

    for (int i = 0; i < glasses.size(); i++) {
        GlassGameObject *glass = glasses[i];
        if (!glass->isActive()) {
            continue;
        }
        glass->doActionAfter();
    }

    checkFrozenGlasses();

    int MAX_NUM_OF_ACTIVE_CIRCLES = 40;
    int realNumOfActiveCircles = 0;
    for (int i = 0; i < circles.size(); i++) {
        CircleGameObject *circle = circles[i];
        if (circle->isActive()) {
            realNumOfActiveCircles++;
            bool insideGlass = false;
            for (int j = 0; j < glasses.size(); j++) {
                GlassGameObject *glass = glasses[j];
                if (glass->isActive() && glass->containsPoint(circle->getShape()->getCenter())) {
                    insideGlass = true;
                    if (!circle->isInsideGlass()) {
                        glass->addCircle(circle);
                    }
                }
            }
            circle->setInsideGlass(insideGlass);
        }
    }
    if (realNumOfActiveCircles < MAX_NUM_OF_ACTIVE_CIRCLES) {
        if (!frozenCircles.empty()) {
            frozenCircles.top()->setActive(true);
            frozenCircles.pop();
        }
    }
}

void PhysicsService::checkFrozenGlasses() {
    if (!frozenGlasses.empty()) {
        GlassGameObject *glass = frozenGlasses.top();
        GlassGameObject *tail = firstGlass->getTail();
        float dist = glassPath.getDistanceBetweenPoints(
                tail->getShape()->getCenter(),
                glass->getShape()->getCenter()
        );
        if (dist >= glassPath.getDistanceBetweenGlasses()) {
            tail->setChild(glass);
            glass->setVisible(true);
            glass->setActive(true);
            frozenGlasses.pop();
        }
    }
}

void PhysicsService::draw(float *projMat, Shader *simpleShader, VertexBuff *vertexBuf) {
    simpleShader->beginRender(vertexBuf, 4, 4);
    simpleShader->setMVP(projMat);
    simpleShader->setColor(1, 1, 1, 1);

    if (gate->isActive()) {
        GLushort indices[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12,
                              13};
        glDrawElements(GL_LINES, 22, GL_UNSIGNED_SHORT, indices);
    } else {
        GLushort indices[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 6, 7, 9, 9, 10, 10, 11, 11, 12, 12, 13};
        glDrawElements(GL_LINES, 20, GL_UNSIGNED_SHORT, indices);
    }

    simpleShader->endRender();
}

void PhysicsService::draw(const DrawableData &drawableDate) {
    drawService->draw(drawableDate.simpleShader, drawableDate.textureShader, drawableDate.projMat);
}

bool PhysicsService::init() {
    return drawService->init();
}

void PhysicsService::reset() {

    ScoreService::getInstance()->reset();

    float distanceBetweenCircles = 0.005f;

    float containerVertices[container->getShape()->verticesSize()];
    container->getShape()->getVertices(containerVertices);

    while (!frozenCircles.empty()) {
        frozenCircles.pop();
    }

    resetCircles(containerVertices[4] + r + distanceBetweenCircles,
                 containerVertices[5] - r - distanceBetweenCircles, 1.0f, r, distanceBetweenCircles,
                 false, 30, 0);

    resetCircles(containerVertices[22] - r - distanceBetweenCircles,
                 containerVertices[23] - r - distanceBetweenCircles, -1.0f, r,
                 distanceBetweenCircles,
                 false, 30, 30);

    resetCircles(-2.0f * (2.0f * r + distanceBetweenCircles),
                 containerVertices[23] - r - distanceBetweenCircles, 1.0f, r,
                 distanceBetweenCircles,
                 true, 40, 60);

    while (!frozenGlasses.empty()) {
        frozenGlasses.pop();
    }
    for (int i = 0; i < 7; i++) {
        GlassGameObject *po = glasses[i];
        po->reset();
        if (i == 0) {
            firstGlass = po;
            po->setActive(true);
            po->setVisible(true);
        } else {
            po->setActive(false);
            po->setVisible(false);
            frozenGlasses.push(po);
        }
    }
}
