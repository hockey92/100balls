#include "ContainerGameObject.h"
#include "Gate.h"

void ContainerGameObject::draw(const DrawableData &drawableDate) {
    Shader *simpleShader = drawableDate.simpleShader;

    simpleShader->setMVP(drawableDate.projMat);
    simpleShader->setColor(1.0f, 1.0f, 1.0f, 1.0f);

    if (gate->isActive()) {
        GLushort indices[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13};
        glDrawElements(GL_LINES, 22, GL_UNSIGNED_SHORT, indices);
    } else {
        GLushort indices[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 6, 7, 9, 9, 10, 10, 11, 11, 12, 12, 13};
        glDrawElements(GL_LINES, 20, GL_UNSIGNED_SHORT, indices);
    }
}

unsigned int ContainerGameObject::type() {
    return getShape()->type();
}

ContainerGameObject::ContainerGameObject(BaseShape *shape, float invM) : GameObject(shape, invM) {
    float vertices[getShape()->verticesSize()];
    getShape()->getVertices(vertices);
    gate = new PhysicsObject(new Gate(vertices), 0.f);
}

PhysicsObject *ContainerGameObject::getGate() {
    return gate;
}

ContainerGameObject::~ContainerGameObject() {
    if (gate) {
        delete gate;
    }
}
