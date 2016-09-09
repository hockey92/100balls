#ifndef INC_100BALLS_WAVFILE_H
#define INC_100BALLS_WAVFILE_H

#include "File.h"

struct WAVHeader {
    char RIFF[4];
    unsigned long ChunkSize;
    char WAVE[4];
    char fmt[4];
    unsigned long Subchunk1Size;
    unsigned short AudioFormat;
    unsigned short NumOfChan;
    unsigned long SamplesPerSec;
    unsigned long bytesPerSec;
    unsigned short blockAlign;
    unsigned short bitsPerSample;
    char Subchunk2ID[4];
    unsigned long Subchunk2Size;
};
struct SoundBuffer {
    WAVHeader *header;
    char *buffer;
    int length;
};

class WAVFile {
public:
    WAVFile(File *file);

    int length() const;

    void *ptr() const;

private:
    int _length;
    File *_file;
};

#endif //INC_100BALLS_WAVFILE_H
