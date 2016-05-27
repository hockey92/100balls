#include <vecmath.h>
#include "Context.h"
#include "Circle.h"
#include "TextureInitializer.h"
#include "CircleGameObject.h"

CircleGameObject::CircleGameObject(float r, float invM) : PhysicsObject(new Circle(r), invM),
                                                          insideGlass(false),
                                                          color(Color(1.0f, 1.0f, 0.0f, 1.0f)) { }

void CircleGameObject::updatePos() {
    PhysicsObject::updatePos();
    if (getShape() != NULL) {
        float lowerBound = -Context::getInstance()->getH();
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

void CircleGameObject::draw(const DrawableData &drawableDate) {
    if (isDeleted()) {
        return;
    }
    Vec2 center = getShape()->getCenter();
    drawableDate.textureShader->setMVP((ndk_helper::Mat4(drawableDate.projMat) * ndk_helper::Mat4::Translation(center.x(), center.y(), 0.0f)).Ptr());
    drawableDate.textureShader->setColor(color);
    drawableDate.textureShader->render();
}

unsigned int CircleGameObject::type() {
    return getShape()->type();
}

Initializer *CircleGameObject::createInitializer() {
    return new TextureInitializer();
}

void CircleGameObject::setColor(const Color &color) {
    this->color = color;
}
