#ifndef TEAPOT_BASESHAPE_H
#define TEAPOT_BASESHAPE_H

#include "IShape.h"
#include "Renderer.h"
#include <pthread.h>

class BaseShape : public IShape {

public:
    BaseShape(Renderer *renderer) : renderer(renderer), _type(0), parent(NULL) { }

    void move(const Vec2 &coords);

    Vec2 getCenter() const;

    void draw(float *projection);

    virtual int getChildCount() const {
        return childCount;
    }

    virtual BaseShape* getChildren(int i);

    virtual int type() const {
        return _type;
    }

protected:
    Vec2 center;
    int childCount;
    BaseShape** children;
    int _type;
    BaseShape* parent;

private:
    Renderer *renderer;
};

#endif //TEAPOT_BASESHAPE_H
