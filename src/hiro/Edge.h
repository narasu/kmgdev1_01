#include "Hiro.h"
#pragma once
namespace Hiro {

    struct Edge {
    public:
        Vector2<float> pointA;
        Vector2<float> pointB;
        Edge();
        Edge(const Vector2<float> _pointA, const Vector2<float> _pointB);
        Vector2<float> getLength();
        Vector2<float> getMidPoint();
        Vector2<float> getNormal(const Vector2<float> _center);
    };

} // Hiro