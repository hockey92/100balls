#ifndef NATIVE_ACTIVITY_ARRAYWRAPPER_H
#define NATIVE_ACTIVITY_ARRAYWRAPPER_H

#include <stddef.h>
#include <pthread.h>

class ArrayWrapper {
public:
    ArrayWrapper() : _size(0), _array(NULL) { }

    ~ArrayWrapper();

    void setValues(float *array, size_t size);

    float get(int i) const;

    size_t size() const;

    ArrayWrapper & operator=(const ArrayWrapper &a);

    float *ptr() {
        return _array;
    }

private:
    size_t _size;
    float *_array;

    void setSize(size_t size);
};

#endif //NATIVE_ACTIVITY_ARRAYWRAPPER_H
