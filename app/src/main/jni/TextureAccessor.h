#ifndef INC_100BALLS_TEXTUREACCESSOR_H
#define INC_100BALLS_TEXTUREACCESSOR_H


#include "ObjectAccessor.h"
#include "Texture.h"

class TextureAccessor : public ObjectAccessor<Texture> {
public:
    TextureAccessor(ObjectAccessor<File> *fileAccessor) {
        this->fileAccessor = fileAccessor;
    }

protected:
    Texture *load(const std::string &filename);

private:
    ObjectAccessor<File> *fileAccessor;

};


#endif //INC_100BALLS_TEXTUREACCESSOR_H
