#include <SFML/Graphics.hpp>

namespace Math {

    template <typename T>
    struct Vector2 {
    public:
        T x, y;

        Vector2() : x(), y() {}

        Vector2(T _x, T _y) : x(_x), y(_y) {}

        Vector2(Vector2<T> &_vector2) : x(_vector2.x), y(_vector2.y) {}


        Vector2& operator*=(const T& _rhScalar) {
            x *= _rhScalar;
            y *= _rhScalar;
            return *this;
        }

        Vector2& operator/=(const T& _rhScalar) {
            x /= _rhScalar;
            y /= _rhScalar;
            return *this;
        }

        Vector2& operator=(const Vector2& _rhVector2) {
            x = _rhVector2.x;
            y = _rhVector2.y;
            return *this;
        }

        Vector2& operator+=(const Vector2& _rhVector2) {
            x += _rhVector2.x;
            y += _rhVector2.y;
            return *this;
        }

        Vector2& operator-=(const Vector2& _rhVector2) {
            x -= _rhVector2.x;
            y -= _rhVector2.y;
            return *this;
        }

        T& operator*=(const Vector2& _rhVector2) {
            return x * _rhVector2.x + y * _rhVector2.y;
        }

        sf::Vector2<T> toSFML() {
            return sf::Vector2<T>(x, y);
        }
    };



}
