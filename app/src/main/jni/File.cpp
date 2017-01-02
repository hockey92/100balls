#include <stddef.h>
#include "File.h"

File::File(const char *fileName, void *buff, int size) {
    this->fileName = std::string(fileName);
    this->buff = buff;
    this->size = size;
}

void *File::getBuff() const {
    return buff;
}

File::~File() {
    if (buff) {
        delete buff;
    }
}
