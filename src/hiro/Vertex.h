#include "Hiro.h"
#include <list>
#pragma once
namespace Hiro {

    struct Vertex {
    public:
        Vector2<float> localPosition;
        Vertex();
        explicit Vertex(Vector2<float> _position);
        Vertex(float _posX, float _posY);
    };

}