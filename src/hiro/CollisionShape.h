#include "Hiro.h"
#include <cmath>
#pragma once

namespace Hiro {
    class CollisionShape {
    public:
        CollisionShape() = default;
        virtual AABB<float> getBounds() = 0;
    protected:
        CollisionData collisionData;
    };
}
