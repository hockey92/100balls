#ifndef INC_100BALLS_FILEACCESSOR_H
#define INC_100BALLS_FILEACCESSOR_H

#include <string>
#include <Map.h>

template<class T>
class ObjectAccessor {
public:
    T *getObject(const std::string &fileName);

protected:
    virtual T *load(const std::string &filename) = 0;

private:
    Map<std::string, T *> objects;
};

template<class T>
T *ObjectAccessor<T>::getObject(const std::string &fileName) {
    T **file = objects.get(fileName);
    if (file == NULL) {
        T *newFile = load(fileName);
        objects.put(fileName, newFile);
        return newFile;
    }
    return *file;
}

#endif //INC_100BALLS_FILEACCESSOR_H
