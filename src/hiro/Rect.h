// It's a rectangle. It does rectangle things.
#include "Hiro.h"
#include <SFML/Graphics.hpp>
#pragma once

namespace Hiro {
    template <typename T>
    struct Rect {
        Vector2<T> min;
        Vector2<T> max;
        T x;
        T y;
        T w;
        T h;

        Rect<T>() : min(V2_ZERO<T>), max(V2_ZERO<T>), x(.0f), y(.0f), w(.0f), h(.0f) {};

        Rect<T>(const Vector2<T> &_min, const Vector2<T> &_max) : min(_min), max(_max) {
            static_assert(std::is_arithmetic_v<T>);
            x = min.x;
            y = min.y;
            w = max.x - min.x;
            h = max.y - min.y;
        }

        Rect<T>(T _w, T _h) : w(_w), h(_h) {
            static_assert(std::is_arithmetic_v<T>);
            x = .0f;
            y = .0f;
            min = V2_ZERO<T>;
            max = Vector2<T>(_w, _h);
        }

        Rect<T>(T _x, T _y, T _w, T _h) : x(_x), y(_y), w(_w), h(_h) {
            static_assert(std::is_arithmetic_v<T>);
            min = Vector2<T>(_x, _y);
            max = Vector2<T>(_x+_w, _y+_h);
        }

        static bool isOverlapping(const Rect<T> &_rectA, const Rect<T> &_rectB) {
            return
                _rectA.x < _rectB.x + _rectB.w &&
                _rectA.x + _rectA.w > _rectB.x &&
                _rectA.y < _rectB.y + _rectB.h &&
                _rectA.h + _rectA.y > _rectB.y;
        }

        //SFML conversions
        explicit Rect<T>(const sf::Rect<T> &_rect) {
            Rect<T>(Vector2<T>(_rect.left, _rect.top), Vector2<T>(_rect.width, _rect.height));
        }

        sf::Rect<T> toSFML() {
            return sf::Rect<T>(x, y, w, h);
        }
    };
}