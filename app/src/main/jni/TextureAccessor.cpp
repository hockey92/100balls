#include "TextureAccessor.h"

Texture *TextureAccessor::load(const std::string &filename) {
    File *file = fileAccessor->getObject(filename);
    if (file == NULL) return NULL;
    return new Texture(new TGAImage(file));
}
