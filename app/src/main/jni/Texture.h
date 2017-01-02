#ifndef NATIVE_ACTIVITY_TEXTURE_H
#define NATIVE_ACTIVITY_TEXTURE_H

#include <GLES2/gl2.h>
#include "File.h"
#include "TGAImage.h"
#include "GLObject.h"

class Texture : public GLObject {

public:
    Texture(TGAImage *image);

    virtual ~Texture();

    void kill();

    void bind(int unit);

    void unbind();

    virtual bool equals(const GLObject &b) const;

    std::string &getFileName() const { return image->getFileName(); }

protected:
    void innerInit();

private:
    GLuint texture;
    TGAImage *image;
};

#endif //NATIVE_ACTIVITY_TEXTURE_H
