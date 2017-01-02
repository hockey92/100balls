#ifndef INC_100BALLS_PROJECTIONMATRIX_H
#define INC_100BALLS_PROJECTIONMATRIX_H

class OrthogonalMatrix {
public:
    void reset();

    void surfaceChanged(float w, float h);

    float *ptr();

    float getH() const;

    float getW() const;

    void setPosition(float x, float y);

    void apply();

    void setAngle(float angle);

private:
    float values[16];
    float initValues[16];
    float w, h, rel, x, y, angle;
};

#endif //INC_100BALLS_PROJECTIONMATRIX_H
