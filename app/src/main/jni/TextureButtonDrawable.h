#ifndef NATIVE_ACTIVITY_TEXTUREBUTTONDRAWABLE_H
#define NATIVE_ACTIVITY_TEXTUREBUTTONDRAWABLE_H

#include "ButtonDrawable.h"

class TextureButtonDrawable : public ButtonDrawable {
public:
    TextureButtonDrawable();

    void draw(const DrawableData &drawableDate);

    unsigned int type();

    bool init();

private:
    VertexBuff *buttonVertex;
    Texture *texture;
};

#endif //NATIVE_ACTIVITY_TEXTUREBUTTONDRAWABLE_H
