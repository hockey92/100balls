#ifndef INC_100BALLS_AUDIOSERVICE_H
#define INC_100BALLS_AUDIOSERVICE_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "WAVFile.h"

class AudioService {
public:
    AudioService();

    void push();

private:
    SLObjectItf engineObj;
    struct android_app *app;
    SLBufferQueueItf bufferQueue;
    WAVFile wavFile;
};


#endif //INC_100BALLS_AUDIOSERVICE_H
