#include <stddef.h>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>
#include "File.h"

File::File(const char *fileName, struct android_app *app) {
    _fileName = std::string(fileName);

    AAsset *asset = AAssetManager_open(app->activity->assetManager, fileName, AASSET_MODE_UNKNOWN);
    _length = AAsset_getLength(asset);
    _buff = new unsigned char[_length];
    AAsset_read(asset, _buff, (size_t) _length);
    AAsset_close(asset);
}

void *File::buff() const {
    return _buff;
}

File::~File() {
    if (_buff) {
        delete _buff;
    }
}
