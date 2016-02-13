#ifndef NATIVE_ACTIVITY_FILEPOOL_H
#define NATIVE_ACTIVITY_FILEPOOL_H

#include <map>
#include <android_native_app_glue.h>
#include "File.h"

class FileBuf {
public:
    static FileBuf *getInstance();

    static void init(struct android_app *app);

    File *getFile();

private:
    FileBuf();

    static struct android_app *app;
    static FileBuf *instance;
    File *file;
};

#endif //NATIVE_ACTIVITY_FILEPOOL_H
