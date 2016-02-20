#include "FileBuf.h"
#include "common.hpp"

FileBuf *FileBuf::instance = NULL;
struct android_app *FileBuf::app = NULL;

FileBuf::FileBuf() {
    ASSERT(FileBuf::app != NULL);
    file = new File("circle.tga", FileBuf::app);
}

FileBuf *FileBuf::getInstance() {
    if (instance == NULL) {
        instance = new FileBuf();
    }
    return instance;
}

void FileBuf::init(struct android_app *app) {
    FileBuf::app = app;
}

File *FileBuf::getFile() {
    return file;
}
