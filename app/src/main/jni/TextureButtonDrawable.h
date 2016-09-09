#ifndef NATIVE_ACTIVITY_TEXTUREBUTTONDRAWABLE_H
#define NATIVE_ACTIVITY_TEXTUREBUTTONDRAWABLE_H

#include "ButtonDrawer.h"

class TextureButtonDrawable : public ButtonDrawer {
public:
    TextureButtonDrawable();

    void draw(const DrawableData &drawableDate);

    unsigned int type();

    bool init();

protected:
    void afterButtonDataIsDefined();

private:
    VertexBuff *buttonVertex;
    Texture *texture;
};

#endif //NATIVE_ACTIVITY_TEXTUREBUTTONDRAWABLE_H
