#ifndef NATIVE_ACTIVITY_FILE_H
#define NATIVE_ACTIVITY_FILE_H

class TGAFile {

public:
    TGAFile(const char *fileName, struct android_app *app);

    ~TGAFile();

    void *getBuf();

    int getW() { return w; }

    int getH() { return h; }

private:
    int h;
    int w;
    void *buf;
};

#endif //NATIVE_ACTIVITY_FILE_H
