#include "Hiro.h"
#include "Edge.h"


namespace Hiro {
    Edge::Edge(Polygon &_parent) : parent(_parent), pointA(V2_ZERO<float>) , pointB(V2_ZERO<float>) {

    }

    Edge::Edge(Polygon &_parent, const Vector2<float> _pointA, const Vector2<float> _pointB) : parent(_parent), pointA(_pointA), pointB(_pointB) {

    }

    Vector2<float> Edge::edgeVector(bool _global) {
        if (_global) {
            return pointB - pointA + parent.position;
        }
        return pointB - pointA;
    }

    Vector2<float> Edge::getMidPoint() {
        return Vector2<float>();
    }

    Vector2<float> Edge::getNormal(const Vector2<float> _center) {
        return Vector2<float>();
    }
} // Hiro