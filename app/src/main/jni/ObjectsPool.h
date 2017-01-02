#ifndef PLATFORMER_OBJECTSPOOL_H
#define PLATFORMER_OBJECTSPOOL_H

#include "Mutex.h"

template<class T>
class ObjectsPool {
public:
    ObjectsPool() : size(0) { }

    int addNewObject(T *object);

    T *getObject(int i);

private:
    T *objects[1000];
    Mutex mutex;
    int size;
};

template<class T>
int ObjectsPool<T>::addNewObject(T *object) {
    mutex.lock();
    int objectIndex = size;
    objects[size++] = object;
    mutex.unlock();
    return objectIndex;
}

template<class T>
T *ObjectsPool<T>::getObject(int i) {
    return objects[i];
}

#endif //PLATFORMER_OBJECTSPOOL_H
