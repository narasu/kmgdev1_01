#include "Hiro.h"
#pragma once

namespace Hiro {
    template <typename T>
    struct Rect {
    public:
        Vector2<T> min;
        Vector2<T> max;


        Rect<T>() : min(V2_ZERO<T>), max(V2_ZERO<T>) {};
        Rect<T>(Vector2<T> _min, Vector2<T> _max) : min(_min), max(_max) {}

        T getInterval() {
            return max.x - min.x;
        }
    };
}