#ifndef NATIVE_ACTIVITY_FILE_H
#define NATIVE_ACTIVITY_FILE_H

#include <string>

class File {

public:
    File(const char *fileName, struct android_app *app);

    virtual ~File();

    void *buff() const;

    std::string fileName() const { return _fileName; }

private:
    std::string _fileName;

    void *_buff;
};

#endif //NATIVE_ACTIVITY_FILE_H
