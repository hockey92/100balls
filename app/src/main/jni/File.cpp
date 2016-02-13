#include <stddef.h>
#include <android/asset_manager.h>
#include "File.h"

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

TGAFile::TGAFile(const char *fileName, struct android_app *app) {
    AAsset *asset = AAssetManager_open(app->assetManager, fileName, AASSET_MODE_UNKNOWN);

    int len = AAsset_getLength(asset);
    buf = new unsigned char[len];
    AAsset_read(asset, buf, (size_t) len);
    AAsset_close(asset);

    h = ((TGAHeader *) buf)->height;
    w = ((TGAHeader *) buf)->width;
}

void *TGAFile::getBuf() {
    return buf + sizeof(TGAHeader);
}

TGAFile::~TGAFile() {
    if (buf) {
        delete buf;
    }
}
