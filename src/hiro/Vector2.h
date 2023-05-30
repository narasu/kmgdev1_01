#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Hiro.h"

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

        Vector2<T>& operator=(const Vector2<T>& _rhVector2) {
            x = _rhVector2.x;
            y = _rhVector2.y;
            return *this;
        }

        bool operator==(const Vector2<T> &_rhVector2) {
            return x == _rhVector2.x && y == _rhVector2.y;
        }

        bool operator!=(const Vector2<T> &_rhVector2) {
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

        Vector2<T> operator-() {
            return Vector2<T>(-x, -y);
        }

        Vector2 operator-(const Vector2& _rhVector2) {
            return Vector2(x-_rhVector2.x, y-_rhVector2.y);
        }

        Vector2& operator-=(const Vector2& _rhVector2) {
            x -= _rhVector2.x;
            y -= _rhVector2.y;
            return *this;
        }

        T operator*(const Vector2& _rhVector2) {
            return x * _rhVector2.x + y * _rhVector2.y;
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

        Vector2<T> clamped(const T _max) {
            if (sqrMagnitude() < _max*_max) {
                return *this;
            }
            Vector2<T> v = *this;
            v.x*v.x > 0 ? v.x = static_cast<T>(sqrt(_max*_max - y*y)) * static_cast<T>(Mathf::sign(v.x)) : v.x = T(0);
            v.y*v.y > 0 ? v.y = static_cast<T>(sqrt(_max*_max - x*x)) * static_cast<T>(Mathf::sign(v.y)) : v.y = T(0);

            return v;
        }

        void clampMagnitude(const T _max) {
            *this = clamped(_max);
        }

        Vector2<T> normalized() {
            static_assert(std::is_floating_point_v<T>);
            return Vector2<T>(x / magnitude(), y / magnitude());
        }

        void normalizeVector() {
            static_assert(std::is_floating_point_v<T>);
            *this /= magnitude();
        }

        //SFML Vector2 conversions

        explicit Vector2<T>(const sf::Vector2<T> &_vector2) {
            x = _vector2.x;
            y = _vector2.y;
        }

        Vector2<T>& operator=(const sf::Vector2<T>& _rhVector2) {
            x = _rhVector2.x;
            y = _rhVector2.y;
            return *this;
        }

        bool operator==(const sf::Vector2<T> _rhVector2) {
            return x == _rhVector2.x && y == _rhVector2.y;
        }

        bool operator!=(const sf::Vector2<T> _rhVector2) {
            return x != _rhVector2.x || y != _rhVector2.y;
        }

        sf::Vector2<T> toSFML() {
            return sf::Vector2<T>(x, y);
        }
    };

    template <typename T>
    static const Vector2<T> V2_ZERO = Vector2(static_cast<T>(0), static_cast<T>(0));
}
