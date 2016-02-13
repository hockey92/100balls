#include <stddef.h>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>
#include "File.h"

File::File(const char *fileName, struct android_app *app) {
    AAsset *asset = AAssetManager_open(app->activity->assetManager, fileName, AASSET_MODE_UNKNOWN);
    int len = AAsset_getLength(asset);
    buf = new unsigned char[len];
    AAsset_read(asset, buf, (size_t) len);
    AAsset_close(asset);
}

void *File::getBuf() const {
    return buf;
}

File::~File() {
    if (buf) {
        delete buf;
    }
}
