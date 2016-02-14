#ifndef NATIVE_ACTIVITY_TEXTURE_H
#define NATIVE_ACTIVITY_TEXTURE_H

#include <GLES2/gl2.h>
#include "File.h"

class Texture {
private:
    GLuint texture;

public:
    Texture(File *file);

    void bind(int unit);

    void unbind();
};

#endif //NATIVE_ACTIVITY_TEXTURE_H
