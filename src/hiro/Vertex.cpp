#include "Hiro.h"
#include "Vertex.h"


namespace Hiro {

    Vertex::Vertex() : localPosition(.0f, .0f), angle(.0f){}

    Vertex::Vertex(Vector2<float> _localPosition, float _angle) : localPosition(_localPosition), angle(_angle){}

    Vertex::Vertex(float _posX, float _posY, float _angle) : localPosition(_posX, _posY), angle(_angle) {}

}