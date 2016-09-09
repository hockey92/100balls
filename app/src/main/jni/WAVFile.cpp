#include "WAVFile.h"

WAVFile::WAVFile(File *file) : _file(file) {

}

void *WAVFile::ptr() const {
    return (char *) (_file->buff() + sizeof(WAVHeader));
}

int WAVFile::length() const {
    return _file->length() - sizeof(WAVFile);
}
