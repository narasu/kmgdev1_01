#include "Hiro.h"
#pragma once
namespace Hiro {

    struct Edge {
    public:
        Vector2<float> pointA;
        Vector2<float> pointB;
        explicit Edge(Triangle &parent);
        Edge(Triangle &parent, Vector2<float> _pointA, Vector2<float> _pointB);
        Vector2<float> edgeVector(bool _global = false);
        Vector2<float> getMidPoint();
        Vector2<float> getNormal(Vector2<float> _center);
    private:
        Triangle &parent;
    };

} // Hiro