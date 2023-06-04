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

        Rect<T>(Vector2<T> _min, Vector2<T> _max) : min(_min), max(_max) {
            x = min.x;
            y = min.y;
            w = max.x - min.x;
            h = max.y - min.y;
        }

        Rect<T>(float _w, float _h) : w(_w), h(_h) {
            x = .0f;
            y = .0f;
            min = V2_ZERO<float>;
            max = Vector2(_w, _h);
        }

        Rect<T>(float _x, float _y, float _w, float _h) : x(_x), y(_y), w(_w), h(_h) {
            min = Vector2(_x, _y);
            max = Vector2(_x+_w, _y+_h);
        }

        explicit Rect<T>(sf::Rect<T> _rect) {
            Rect<T>(Vector2<T>(_rect.left, _rect.top), Vector2<T>(_rect.width, _rect.height));
        }
        float xScalar() {
            return max.x - min.x;
        }

        Vector2<T> xInterval() {
            return Vector2<T>(min.x, max.x);
        }

        static bool isOverlapping(Rect<T> _rectA, Rect<T> _rectB) {
            return
                _rectA.x < _rectB.x + _rectB.w &&
                _rectA.x + _rectA.w > _rectB.x &&
                _rectA.y < _rectB.y + _rectB.h &&
                _rectA.h + _rectA.y > _rectB.y;
        }
    };
}