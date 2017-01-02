#ifndef INC_100BALLS_RENDERER_H
#define INC_100BALLS_RENDERER_H

#include "Color.h"

class Renderer {
public:
    Renderer() : filled(false), angel(0), x(0), y(0) { }

    virtual void render() = 0;

    void setColor(Color color);

    void setColor(float r, float g, float b, float a);

    void setPosition(float x, float y);

    void move(float x, float y);

    void setFilled(bool filled);

    void setAngel(float angel);

    void rotate(float angle);

protected:
    bool filled;
    Color color;
    float x;
    float y;
    float angel;
};

#endif //INC_100BALLS_RENDERER_H
