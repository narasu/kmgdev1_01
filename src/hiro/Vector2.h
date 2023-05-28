#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#pragma once

//definitions included in header file because of generic type

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

        double magnitude() {
            return sqrt(double(sqrMagnitude()));
        }

        Vector2<double> normalized() {
            return Vector2<double>(double(x) / magnitude(), double(y) / magnitude());
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
}
