#include "ArrayWrapper.h"
#include "common.hpp"

void ArrayWrapper::setSize(size_t size) {
    if (_array != NULL) {
        delete[] _array;
    }
    this->_size = size;
    _array = new float[size];
}

void ArrayWrapper::setValues(float *array, size_t size) {
    setSize(size);
    for (size_t i = 0; i < size; i++) {
        this->_array[i] = array[i];
    }
}

ArrayWrapper::~ArrayWrapper() {
    if (_array) {
        delete[] _array;
    }
}

float ArrayWrapper::get(int i) const {
    ASSERT(i < _size);
    return _array[i];
}

size_t ArrayWrapper::size() const {
    return _size;
}

ArrayWrapper &ArrayWrapper::operator=(const ArrayWrapper &a) {
    setSize(a.size());
    for (int i = 0; i < _size; i++) {
        _array[i] = a._array[i];
    }
    return *this;
}