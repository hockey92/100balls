#include "FileService.h"

FileService::FileService(AAssetManager *assetManager) : assetManager(assetManager) { }

File *FileService::load(const std::string &filename) {
    AAsset *asset = AAssetManager_open(assetManager, filename.c_str(), AASSET_MODE_UNKNOWN);
    int size = AAsset_getLength(asset);
    void *buff = new unsigned char[size];
    AAsset_read(asset, buff, (size_t) size);
    AAsset_close(asset);
    return new File(filename.c_str(), buff, size);
}
