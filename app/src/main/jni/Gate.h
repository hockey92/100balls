#ifndef NATIVE_ACTIVITY_GATE_H
#define NATIVE_ACTIVITY_GATE_H

#include "Segment.h"
#include "ArrayWrapper.h"

class Gate : public Segment {
public:
    Gate(float *vertices);
};

#endif //NATIVE_ACTIVITY_GATE_H
