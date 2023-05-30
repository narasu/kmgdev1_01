#include "Hiro.h"
#pragma once

namespace Hiro {
    template <typename T>
    struct AABB {
        Vector2<T> min;
        Vector2<T> max;

        T getInterval() {
            return max.x - min.x;
        }
    };
}