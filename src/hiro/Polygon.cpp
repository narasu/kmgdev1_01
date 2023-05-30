#include "Hiro.h"

namespace Hiro {
    Polygon::Polygon(Vector2<float> _pointA, Vector2<float> _pointB, Vector2<float> _pointC) {


        vertices[0] = Vertex(_pointA);
        vertices[1] = Vertex(_pointB);
        vertices[2] = Vertex(_pointC);

        edges[0] = Edge(_pointA, _pointB);
        edges[1] = Edge(_pointB, _pointC);
        edges[2] = Edge(_pointC, _pointA);
    }
}