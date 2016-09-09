#ifndef NATIVE_ACTIVITY_FILEPOOL_H
#define NATIVE_ACTIVITY_FILEPOOL_H

#include <map>
#include <android_native_app_glue.h>
#include "File.h"
#include "MapWrapper.h"
#include <string>

class FileBuf {
public:
    static FileBuf *getInstance();

    static void init(struct android_app *app);

    File *getFile(std::string fileName);

    File *getCircle();

    File *getFontImage();

    File *getPauseButton();

    File* getSound();

private:
    FileBuf();

    static struct android_app *app;
    static FileBuf *instance;
    File *circle;
    File *fontImage;
    File *pauseButton;
    File *sound;

    MapWrapper<std::string, File *> _files;
};

#endif //NATIVE_ACTIVITY_FILEPOOL_H
