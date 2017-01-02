#include "ContainerGameObject.h"
#include "Gate.h"
#include "Container.h"

unsigned short ContainerGameObject::openedGateIndices[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13};
unsigned short ContainerGameObject::closedGateIndices[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 6, 7, 9, 9, 10, 10, 11, 11, 12, 12, 13};

ContainerGameObject::ContainerGameObject(float invM, RendererFactory *rendererFactory) : GameObject(new Container(), invM) {
    int size = getShape()->verticesSize();
    float vertices[size];
    getShape()->getVertices(vertices);

    gate = new PhysicsObject(new Gate(vertices), 0.f);
    renderer = rendererFactory->createGeometryRenderer(vertices, size);
    renderer->setColor(Color(1.f, 1.f, 1.f, 1.f));
}

void ContainerGameObject::draw() {
    if (gate->isActive()) {
        renderer->render(openedGateIndices, 22);
    } else {
        renderer->render(closedGateIndices, 20);
    }
}

PhysicsObject *ContainerGameObject::getGate() {
    return gate;
}

ContainerGameObject::~ContainerGameObject() {
    delete gate;
    delete renderer;
}
