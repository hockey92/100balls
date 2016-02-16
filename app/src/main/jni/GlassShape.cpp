#include "GlassShape.h"
#include "Segment.h"

GlassShape::GlassShape() : BaseShape() {

    float points[] = {
            -0.23f, 0.30f,
            -0.15f, -0.30f,
            0.15f, -0.30f,
            0.23f, 0.30f
    };

    childCount = 3;
    children = new BaseShape *[3];
    for (int i = 0; i < childCount; i++) {
        children[i] = new Segment(
                this,
                Vec2(points[i * 2], points[i * 2 + 1]),
                Vec2(points[i * 2 + 2], points[i * 2 + 3])
        );
    }

//    childCount = 2;
//    children = new BaseShape *[2];
//    children[0] = new Segment(
//            Vec2(points[2], points[3]),
//            Vec2(points[4], points[5])
//    );
//    children[1] = new Segment(
//            Vec2(points[4], points[5]),
//            Vec2(points[6], points[7])
//    );
}
