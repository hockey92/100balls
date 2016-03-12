#ifndef NATIVE_ACTIVITY_FONT_H
#define NATIVE_ACTIVITY_FONT_H

#include "TGAImage.h"
#include "VertexBuf.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureShader.h"
#include <string>

class Font {
public:
    Font(TGAImage *image);

    ~Font();

    void init();

    void renderInteger(unsigned int num, TextureShader *shader, float *mvp, float x, float y);

    void renderInteger(unsigned int num, TextureShader *shader, float *mvp, const Vec2 &pos);

    void renderText(const std::string& text, TextureShader *shader, float *mvp, float x, float y);

    void renderText(const std::string& text, TextureShader *shader, float *mvp, const Vec2 &pos);

private:
    TGAImage *image;
    VertexBuf *fontBuf[300];
    Texture *texture;

    void bfs();

    bool checkRange(int value, int lower, int upper);
};

#endif //NATIVE_ACTIVITY_FONT_H
