#include "Renderer.h"

void Renderer::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void Renderer::setColor(Color color) {
    this->color = color;
}

void Renderer::setColor(float r, float g, float b, float a) {
    this->color = Color(r, g, b, a);
}

void Renderer::setFilled(bool filled) {
    this->filled = filled;
}

void Renderer::setAngel(float angel) {
    this->angel = angel;
}

void Renderer::move(float x, float y) {
    this->x += x;
    this->y += y;
}

void Renderer::rotate(float angle) {
    this->angel += angle;
}
