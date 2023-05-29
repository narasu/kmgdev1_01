#pragma once

namespace Hiro {
    class Mathf {
    public:
        template <typename T>
        static T distance(Vector2<T> _lhVector, Vector2<T> _rhVector) {
            Vector2<T> v = _rhVector - _lhVector;
            return v.magnitude();
        }

        template <typename T>
        static int sign(T _number) {
            return (0 < _number) - (_number < 0);
        }
    };
}