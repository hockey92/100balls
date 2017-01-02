#include "OrthogonalMatrix.h"
#include <math.h>

void OrthogonalMatrix::reset() {
    for (int i = 0; i < 16; i++) {
        values[i] = initValues[i];
    }
}

void OrthogonalMatrix::surfaceChanged(float w, float h) {
    this->w = w;
    this->h = h;
    this->rel = w / h;
    for (int i = 0; i < 16; i++) {
        initValues[i] = 0;
    }
    initValues[0] = 1;
    initValues[5] = rel;
    initValues[10] = 1;
    initValues[15] = 1;

    reset();
}

float *OrthogonalMatrix::ptr() {
    return values;
}

void OrthogonalMatrix::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

float OrthogonalMatrix::getH() const {
    return 1.0f / rel;
}

float OrthogonalMatrix::getW() const {
    return 1;
}

void OrthogonalMatrix::apply() {
    values[0] = angle == 0 ? 1 : cosf(angle);
    values[1] = angle == 0 ? 0 : -sinf(angle) * rel;
    values[4] = angle == 0 ? 0 : sinf(angle);
    values[5] = angle == 0 ? rel : cosf(angle) * rel;
    values[10] = 1;
    values[12] = x;
    values[13] = y * rel;
    values[15] = 1;
}

void OrthogonalMatrix::setAngle(float angle) {
    this->angle = -angle;
}
