#include "Hiro.h"
namespace Hiro {

    struct Triangle {
    public:
        Triangle(Vector2<float> _pointA, Vector2<float> _pointB, Vector2<float> _pointC);
        Vector2<float> position;
        Vector2<float> centroid;
        std::vector<Edge> edges;
        Vertex vertices[3];

        AABB<float> bounds;


    };

}