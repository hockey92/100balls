#ifndef PLATFORMER_FILESERVICE_H
#define PLATFORMER_FILESERVICE_H

#include <android/asset_manager.h>
#include "Map.h"
#include "File.h"
#include "ObjectAccessor.h"

class FileService : public ObjectAccessor<File> {
public:
    FileService(AAssetManager *assetManager);

protected:
    File *load(const std::string &filename);

private:
    AAssetManager *assetManager;
};

#endif //PLATFORMER_FILEMANAGER_H
