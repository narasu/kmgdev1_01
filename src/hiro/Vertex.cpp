#include "Hiro.h"
#include "Vertex.h"


namespace Hiro {

    Vertex::Vertex() : localPosition(.0f, .0f){}

    Vertex::Vertex(Vector2<float> _position) : localPosition(_position){}

    Vertex::Vertex(float _posX, float _posY) : localPosition(_posX, _posY) {}

}