#ifndef NATIVE_ACTIVITY_FILE_H
#define NATIVE_ACTIVITY_FILE_H

class File {

public:
    File(const char *fileName, struct android_app *app);
    ~File();
    void *getBuf() const;

private:
    void *buf;
};

#endif //NATIVE_ACTIVITY_FILE_H
