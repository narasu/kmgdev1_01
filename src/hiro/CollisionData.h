#include "hiro.h"
#pragma once
namespace Hiro {

    struct CollisionData {
    public:
        AABB<float> bounds;
        bool isColliding(CollisionShape &_other);
    };

}