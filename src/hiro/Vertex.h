#include "Hiro.h"
#include <list>
#pragma once
namespace Hiro {

    struct Vertex {
    public:
        Vertex();
        explicit Vertex(Vector2<float> _localPosition, float _angle);
        Vertex(float _posX, float _posY, float _angle);
        Vector2<float> localPosition;
        float angle;
    };

}