// General math functions and shorthand

#include "Hiro.h"
#include <cmath>
#pragma once

namespace Hiro {
    class Mathf {
    public:

        template <typename T>
        static int sign(T _number) {
            return (0 < _number) - (_number < 0);
        }

        static constexpr float RAD2DEG = 180 / M_PI;
    };
}