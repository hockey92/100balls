#ifndef NATIVE_ACTIVITY_FILE_H
#define NATIVE_ACTIVITY_FILE_H

#include <string>
#include <android/asset_manager_jni.h>

class File {

public:
    File(const char *fileName, void *buff, int size);

    virtual ~File();

    void *getBuff() const;

    std::string& getFileName() { return fileName; }

    long getSize() const { return size; }

private:
    std::string fileName;
    void *buff;
    long size;
};

#endif //NATIVE_ACTIVITY_FILE_H
