#include <common.h>
#include "GameService.h"
#include <sstream>

GameService::GameService(float w, float h, RendererFactory *rendererFactory) {
    this->w = w;
    this->h = h;
    r = 0.0355f;
    time = 0;
    lastDrawn = -1;
    glassPath = new GlassPath(h, NUM_OF_GLASSES);
    container = new ContainerGameObject(0.f, rendererFactory);

    fontRenderer = rendererFactory->createFontRenderer();

    for (int i = 0; i < 10; i++) {
        CircleGameObject *circleGO = new CircleGameObject(r, 1.f, -h, rendererFactory);
        addPhysicsObjects(circleGO);
        circles.push_back(circleGO);
    }

    addPhysicsObjects(container);
    gate = container->getGate();
    addPhysicsObjects(gate);

    for (int i = 0; i < NUM_OF_GLASSES; i++) {
        GlassGameObject *glassGO = new GlassGameObject(glassPath, rendererFactory, &score);
        addPhysicsObjects(glassGO);
        glasses.push_back(glassGO);
    }

    reset();
}

void GameService::resetCircles(float initX, float initY,
                               float direction, float r,
                               float distanceBetweenCircles, bool active,
                               int numOfCircles, int startCircleNumber) {
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

void GameService::open() {
    gate->setActive(false);
}

void GameService::close() {
    gate->setActive(true);
}

void GameService::doActionBefore() {

}

void GameService::doActionAfter() {

    GameObject::incrementCycleNumber();

    bool gameOver = true;

    for (int i = 0; i < glasses.size(); i++) {
        GlassGameObject *glass = glasses[i];
        if (!glass->isActive()) {
            continue;
        }
        gameOver = false;
        glass->doActionAfter(&firstGlass);
    }

    if (gameOver) {
        setStatus(STOPPED);
        return;
    }

    checkFrozenGlasses();

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

void GameService::checkFrozenGlasses() {
    if (!frozenGlasses.empty()) {
        GlassGameObject *glass = frozenGlasses.top();
        GlassGameObject *tail = firstGlass->getTail();
        float dist = glassPath->getDistanceBetweenPoints(tail->getShape()->getCenter(),
                                                         glass->getShape()->getCenter());
        if (dist >= glassPath->getDistanceBetweenGlasses()) {
            tail->setChild(glass);
            glass->setVisible(true);
            glass->setActive(true);
            frozenGlasses.pop();
        }
    }
}

void GameService::reset() {
    float distanceBetweenCircles = 0.005f;

    float containerVertices[container->getShape()->verticesSize()];
    container->getShape()->getVertices(containerVertices);

    while (!frozenCircles.empty()) {
        frozenCircles.pop();
    }

    resetCircles(containerVertices[4] + r + distanceBetweenCircles,
                 containerVertices[5] - r - distanceBetweenCircles,
                 1.0f, r, distanceBetweenCircles, false, 10, 0);

//    resetCircles(containerVertices[22] - r - distanceBetweenCircles,
//                 containerVertices[23] - r - distanceBetweenCircles,
//                 -1.0f, r, distanceBetweenCircles, false, 30, 30);
//
//    resetCircles(-2.0f * (2.0f * r + distanceBetweenCircles),
//                 containerVertices[23] - r - distanceBetweenCircles,
//                 1.0f, r, distanceBetweenCircles, false, 40, 60);

    while (!frozenGlasses.empty()) {
        frozenGlasses.pop();
    }
    for (int i = 0; i < NUM_OF_GLASSES; i++) {
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

void GameService::draw(float currentTime) {

    int cycleNumber = GameObject::getCycleNumber();
    cycleNumber--;
    if (cycleNumber < 0) {
        cycleNumber = 99;
    }

    lastDrawn= cycleNumber;

//    if (lastDrawn == -1) {
//        lastDrawn = cycleNumber;
//    } else {
//        lastDrawn = (lastDrawn + 1) % 100;
//    }

    LOGE("cycle number %d", lastDrawn);

    container->draw(lastDrawn);

    for (int i = 0; i < circles.size(); i++) {
        float delta = currentTime - time;
        delta = delta < 0 ? 0 : delta;
        circles[i]->draw(delta);
    }

    for (int i = 0; i < glasses.size(); i++) {
        float delta = currentTime - time;
        delta = delta < 0 ? 0 : delta;
        glasses[i]->draw(delta);
    }

    std::ostringstream ss;
    ss << score.getValue();
    fontRenderer->setText(ss.str());
    fontRenderer->setPosition(0, -0.2f);
    fontRenderer->render();


}

GameService::~GameService() {
    delete glassPath;
}

void GameService::nextFrame(float dt) {
    PhysicsService::nextFrame(dt);
    time += dt;
}
