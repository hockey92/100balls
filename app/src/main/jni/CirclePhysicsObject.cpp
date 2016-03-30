#include <vecmath.h>
#include "CirclePhysicsObject.h"
#include "GameCoords.h"
#include "Circle.h"
#include "TextureInitializer.h"

CirclePhysicsObject::CirclePhysicsObject(float r, float invM) : PhysicsObject(new Circle(r), invM),
                                                                insideGlass(false) { }

void CirclePhysicsObject::updatePos() {
    PhysicsObject::updatePos();
    if (getShape() != NULL) {
        float lowerBound = -GameCoords::getInstance()->getCoords(SCREEN_BORDERS)->getData()[HIGH];
        if (getShape()->getCenter().y() < lowerBound) {
            setDeleted(true);
        }
    }
}

bool CirclePhysicsObject::isInsideGlass() {
    return insideGlass;
}

void CirclePhysicsObject::setInsideGlass(bool insideGlass) {
    this->insideGlass = insideGlass;
}

void CirclePhysicsObject::draw(const DrawableData &drawableDate) {
    if (isDeleted()) {
        return;
    }
    Vec2 center = getShape()->getCenter();
    drawableDate.textureShader->setMVP((ndk_helper::Mat4(drawableDate.projMat) *
                                        ndk_helper::Mat4::Translation(center.x(), center.y(),
                                                                      0.0f)).Ptr());
    drawableDate.textureShader->setColor(1.0f, 1.0f, 0.0f, 0.0f);
    drawableDate.textureShader->render();
}

unsigned int CirclePhysicsObject::type() {
    return getShape()->type();
}

Initializer *CirclePhysicsObject::createInitializer() {
    return new TextureInitializer();
}
