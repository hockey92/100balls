#include "Texture.h"

struct TGAHeader {
    unsigned char idSize;
    unsigned char colorMapType;
    unsigned char imageType;
    unsigned short paletteStart;
    unsigned short paletteLength;
    unsigned char paletteBits;
    unsigned short xOrigin;
    unsigned short yOrigin;
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char descriptor;
} __attribute__ ((packed));

Texture::Texture(File *file) {
    texture = 0;

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPixelStorei(GL_PACK_ALIGNMENT, 4);

    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            ((TGAHeader *) file->getBuf())->width,
            ((TGAHeader *) file->getBuf())->height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            (file->getBuf() + sizeof(TGAHeader))
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(int unit) {
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
