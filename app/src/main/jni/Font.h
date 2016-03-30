#ifndef NATIVE_ACTIVITY_FONT_H
#define NATIVE_ACTIVITY_FONT_H

#include "TGAImage.h"
#include "VertexBuff.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureShader.h"
#include "Color.h"
#include <string>

class Font {
public:
    Font(TGAImage *image);

    ~Font();

    void init();

    void setColor(const Color &color);

    void renderInteger(unsigned int num, TextureShader *shader, float *mvp, float x, float y);

    void renderInteger(unsigned int num, TextureShader *shader, float *mvp, const Vec2 &pos);

    void renderText(const std::string &text, TextureShader *shader, float *mvp, float x, float y);

    void renderText(const std::string &text, TextureShader *shader, float *mvp, const Vec2 &pos);

private:
    TGAImage *image;
    std::pair<VertexBuff *, float> fontBuff[300]; // pair(height, buff)
    Texture *texture;

    void bfs(char firstSymbol, size_t count, int yPosition);

    bool checkRange(int value, int lower, int upper);

    float maxLetterHigh;

    Color color;
};

#endif //NATIVE_ACTIVITY_FONT_H
