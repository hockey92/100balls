#ifndef NATIVE_ACTIVITY_FONT_H
#define NATIVE_ACTIVITY_FONT_H

#include "TGAImage.h"
#include "VertexBuff.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureShader.h"
#include "Color.h"
#include "RendererFactory.h"
#include "ObjectAccessor.h"
#include <string>

class Font {
public:
    Font(RendererFactory *rendererFactory, ObjectAccessor<File> *fileAccessor);

    virtual ~Font();

    void setColor(const Color &color);

    void renderText(const std::string &text, float x, float y);

private:
    RendererFactory *rendererFactory;

    TGAImage *image;
    Renderer *symbolRenderers[300];
    Texture *texture;

    void bfs(char firstSymbol, size_t count, int yPosition);

    bool checkRange(int value, int lower, int upper);

    float maxLetterHigh;

    Color color;
};

#endif //NATIVE_ACTIVITY_FONT_H
