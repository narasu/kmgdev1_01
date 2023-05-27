#include "Vector2.h"
#include <cmath>

#pragma once
namespace Hiro {
    class CollisionShape {
    public:
        CollisionShape();
        CollisionShape(Vector2<float> _localPosition, float _radius = 1.0f);
        CollisionShape(float _localX, float _localY, float _radius = 1.0f);
        Vector2<float> localPosition;
        float radius;
        bool isColliding(CollisionShape &_collisionShape);


        // get sqrMagnitude m of delta between 2 vectors (in other words, distance)
        // bool isColliding = m - (r1 + r2)^2 <= 0
    };

}
