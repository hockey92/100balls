#ifndef NATIVE_ACTIVITY_DRAWUTILS_H
#define NATIVE_ACTIVITY_DRAWUTILS_H

class DrawUtils {
public:
    static float *createCoordinatesForShader(float *xyCoords, float zCoord, int size);

    static float *createCoordinatesForTextureShader(float down, float up, float left, float right,
                                                    float texDown, float texUp,
                                                    float texLeft, float texRight);
};

#endif //NATIVE_ACTIVITY_DRAWUTILS_H
