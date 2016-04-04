#include "SimpleShape.h"

void SimpleShape::getVertices(float *vertices) {
    for (int i = 0; i < verticesSize(); i++) {
        vertices[i] = array.get(i);
    }
}

int SimpleShape::verticesSize() {
    return array.size();
}
