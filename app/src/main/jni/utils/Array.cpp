#include "Array.h"
#include "common.h"

void Array::setSize(int size) {
    if (_array != NULL) {
        delete[] _array;
    }
    this->_size = size;
    _array = new float[size];
}

void Array::setValues(float *array, int size) {
    setSize(size);
    for (size_t i = 0; i < size; i++) {
        this->_array[i] = array[i];
    }
}

Array::~Array() {
    if (_array) {
        delete[] _array;
    }
}

float Array::get(int i) const {
    ASSERT(i < _size);
    return _array[i];
}

int Array::size() const {
    return _size;
}

Array &Array::operator=(const Array &a) {
    setSize(a.size());
    for (int i = 0; i < _size; i++) {
        _array[i] = a._array[i];
    }
    return *this;
}