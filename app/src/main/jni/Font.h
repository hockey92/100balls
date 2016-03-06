#ifndef NATIVE_ACTIVITY_FONT_H
#define NATIVE_ACTIVITY_FONT_H

#include "TGAImage.h"
#include "VertexBuf.h"
#include "Shader.h"
#include "Texture.h"
#include "TextureShader.h"

class Font {
public:
    Font(TGAImage *image);

    ~Font();

    void init();

    void renderInteger(unsigned int num, TextureShader *shader, float *mvp, float y);

private:
    TGAImage *image;
    VertexBuf *fontBuf[300];
    Texture* texture;

    void bfs();

    bool checkRange(int value, int lower, int upper);
};

#endif //NATIVE_ACTIVITY_FONT_H
