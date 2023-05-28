#include "Vector2.h"
#include <cmath>
#pragma once

namespace Hiro {
    class CollisionShape {
    public:
        CollisionShape() = default;
        virtual bool isColliding(CollisionShape &_collisionShape) = 0;
        virtual Vector2<float> getLocalPosition() = 0;
    };
}
