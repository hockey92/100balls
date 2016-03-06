#ifndef NATIVE_ACTIVITY_TEXTRENDERER_H
#define NATIVE_ACTIVITY_TEXTRENDERER_H

#include "TextureShader.h"
#include "Font.h"

class TextRenderer {
public:
    TextRenderer(TextureShader* shader, Font* font);

private:
    TextureShader* shader;
};

#endif //NATIVE_ACTIVITY_TEXTRENDERER_H
