#include "Circle.h"
#include "CircleGameObject.h"
#include "ScreenService.h"

CircleGameObject::CircleGameObject(float r, float invM, float lowerBound,
                                   RendererFactory *rendererFactory)
        : PhysicsObject(new Circle(r, NULL), invM),
          insideGlass(false),
          color(Color(1.0f, 1.0f, 0.0f, 1.0f)),
          lowerBound(lowerBound) {

    renderer = rendererFactory->createTextureRenderer(2.f * r, 2.f * r, "circle.tga");

}

void CircleGameObject::updatePos() {
    PhysicsObject::updatePos();
    if (getShape() != NULL) {
        if (getShape()->getCenter().y() < lowerBound) {
            setDeleted(true);
        }
    }
}

bool CircleGameObject::isInsideGlass() {
    return insideGlass;
}

void CircleGameObject::setInsideGlass(bool insideGlass) {
    this->insideGlass = insideGlass;
}

void CircleGameObject::draw() {
    if (isDeleted()) {
        return;
    }
    renderer->setColor(color);
    Vec2 center = getShape()->getCenter();
    renderer->setPosition(center.x(), center.y());
    renderer->render();
}

unsigned int CircleGameObject::type() {
    return getShape()->type();
}

void CircleGameObject::setColor(const Color &color) {
    this->color = color;
}
