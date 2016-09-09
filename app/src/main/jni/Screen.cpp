#include "Screen.h"

Screen::Screen(float realW, float realH) : _realW(realW), _realH(realH) {
    float values[16];

    for (int i = 0; i < 16; i++) {
        values[i] = 0;
    }

    float rel = realW / realH;

    _w = 1.0f;
    _h = 1 / rel;

    values[0] = 1.0f;
    values[5] = rel;
    values[10] = -1.0f;
    values[15] = 1.0f;

    _projMat.setValues(values, 16);
}
