#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "hiro.h"

#pragma once

namespace Hiro {
    template <class T>
    struct Vector2 {
    public:
        T x, y;

        Vector2() {
            static_assert(std::is_arithmetic_v<T>);
        }

        Vector2<T>(T _x, T _y) : x(_x), y(_y) {
            static_assert(std::is_arithmetic_v<T>);
        }

        Vector2<T>(const sf::Vector2<T> &_vector2) {
            x = _vector2.x;
            y = _vector2.y;
        }

        template <typename U>
        explicit Vector2<T>(Vector2<U> &_vector2) {
            if (std::is_same_v<T, U>) {
                x = _vector2.x;
                y = _vector2.y;
                return;
            }
            x = static_cast<T>(_vector2.x);
            y = static_cast<T>(_vector2.y);
        }


        template <typename U>
        Vector2<T>& operator=(const Vector2<U>& _rhVector2) {
            if (std::is_same_v<T, U>) {
                x = _rhVector2.x;
                y = _rhVector2.y;
                return *this;
            }
            x = static_cast<T>(_rhVector2.x);
            y = static_cast<T>(_rhVector2.y);
            return *this;
        }

        Vector2<T>& operator=(const Vector2<T>& _rhVector2) {
            x = _rhVector2.x;
            y = _rhVector2.y;
            return *this;
        }

        Vector2<T> operator-() {
            Vector2<T> v;
            v.x = -x;
            v.y = -y;
            return v;
        }

        Vector2<T>& operator=(const sf::Vector2<T>& _rhVector2) {
            x = _rhVector2.x;
            y = _rhVector2.y;
            return *this;
        }

        bool operator==(sf::Vector2<T> _rhVector2) {
            return x == _rhVector2.x && y == _rhVector2.y;
        }

        bool operator!=(sf::Vector2<T> _rhVector2) {
            return x != _rhVector2.x || y != _rhVector2.y;
        }

        Vector2 operator+(const Vector2& _rhVector2) {
            return Vector2<T>(x+_rhVector2.x, y+_rhVector2.y);
        }

        Vector2& operator+=(const Vector2& _rhVector2) {
            x += _rhVector2.x;
            y += _rhVector2.y;
            return *this;
        }

        Vector2 operator-(const Vector2& _rhVector2) {
            return Vector2(x-_rhVector2.x, y-_rhVector2.y);
        }

        Vector2& operator-=(const Vector2& _rhVector2) {
            x -= _rhVector2.x;
            y -= _rhVector2.y;
            return *this;
        }

        Vector2 operator*(const T& _rhScalar) {
            return Vector2(x*_rhScalar, y*_rhScalar);
        }

        Vector2& operator*=(const T& _rhScalar) {
            x *= _rhScalar;
            y *= _rhScalar;
            return *this;
        }

        Vector2 operator/(const T& _rhScalar) {
            return Vector2(x/_rhScalar, y/_rhScalar);
        }

        Vector2& operator/=(const T& _rhScalar) {
            x /= _rhScalar;
            y /= _rhScalar;
            return *this;
        }

        T operator*(const Vector2& _rhVector2) {
            return x * _rhVector2.x + y * _rhVector2.y;
        }

        friend std::ostream& operator<<(std::ostream& _out,const Vector2 &_rhVector2) {
            _out << "(" << _rhVector2.x << ", " << _rhVector2.y << ")" << std::endl;
            return _out;
        }

        T sqrMagnitude() {
            return x*x + y*y;
        }

        T magnitude() {
            return sqrt(sqrMagnitude());
        }

        void clampMagnitude(T _max) {
            // sqrMagnitude = _max*_max
            // x*x + y*y = _max*_max
            // x*x = _max*_max - y*y
            // y*y = _max*_max - x*x
            if (sqrMagnitude() < _max*_max) {
                return;
            }

            x*x > 0 ? x = static_cast<T>(sqrt(_max*_max - y*y)) * static_cast<T>(Mathf::sign(x)) : x = T(0);
            y*y > 0 ? y = static_cast<T>(sqrt(_max*_max - x*x)) * static_cast<T>(Mathf::sign(y)) : y = T(0);
        }

        Vector2<T> clamped(T _max) {
            if (sqrMagnitude() < _max*_max) {
                return *this;
            }
            Vector2<T> v = *this;
            v.x*v.x > 0 ? v.x = static_cast<T>(sqrt(_max*_max - y*y)) * static_cast<T>(Mathf::sign(v.x)) : v.x = T(0);
            v.y*v.y > 0 ? v.y = static_cast<T>(sqrt(_max*_max - x*x)) * static_cast<T>(Mathf::sign(v.y)) : v.y = T(0);

            return v;
        }

        Vector2<T> normalized() {
            static_assert(std::is_floating_point_v<T>);
            return Vector2<T>(x / magnitude(), y / magnitude());
        }

        void normalizeVector() {
            *this /= magnitude();
        }

        double distanceTo(Vector2 _rhVector) {
            return (_rhVector - *this).magnitude();
        }

        //conversion to SFML Vector2 for use in SFML methods that only take sf::Vector2<T> as argument
        sf::Vector2<T> toSFML() {
            return sf::Vector2<T>(x, y);
        }
    };

    template <typename T>
    static const Vector2<T> V2_ZERO = Vector2(static_cast<T>(0), static_cast<T>(0));

    template <typename T>
    static const Vector2<T> V2_ONE = Vector2(static_cast<T>(1), static_cast<T>(1));

    template <typename T>
    static const Vector2<T> V2_DOWN = Vector2(static_cast<T>(0), static_cast<T>(1));

    template <typename T>
    static const Vector2<T> V2_UP = Vector2(static_cast<T>(0), static_cast<T>(-1));

    template <typename T>
    static const Vector2<T> V2_RIGHT = Vector2(static_cast<T>(1), static_cast<T>(0));

    template <typename T>
    static const Vector2<T> V2_LEFT = Vector2(static_cast<T>(-1), static_cast<T>(0));
}
