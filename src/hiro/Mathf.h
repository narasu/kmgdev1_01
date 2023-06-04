// General math functions and shorthand

#include "Hiro.h"
#include <cmath>
#pragma once

namespace Hiro {
    class Mathf {
    public:

        template <typename T>
        static int sign(T _number) {
            static_assert(std::is_arithmetic_v<T>);
            return (0 < _number) - (_number < 0);
        }

        template <typename T>
        static float signf(T _number) {
            static_assert(std::is_arithmetic_v<T>);
            return static_cast<float>((0 < _number) - (_number < 0));
        }

        template <typename T>
        static T clamp(T _number, T _min, T _max) {
            static_assert(std::is_arithmetic_v<T>);
            return _number > _min && _number < _max ? _number : _number < _min ? _min : _max;
        }

        template <typename T>
        static T min(T _number, T _min) {
            static_assert(std::is_arithmetic_v<T>);
            return _number > _min ? _number : _min;
        }

        static constexpr float RAD2DEG = 180 / M_PI;
    };
}