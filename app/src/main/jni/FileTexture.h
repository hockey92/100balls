#ifndef NATIVE_ACTIVITY_FILETEXTURE_H
#define NATIVE_ACTIVITY_FILETEXTURE_H

class FileTexture {
public:
    FileTexture(struct android_app *state);

private:
    int w;
    int h;
    void *buff;
};

#endif //NATIVE_ACTIVITY_FILETEXTURE_H
