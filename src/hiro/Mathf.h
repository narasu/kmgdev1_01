//
// Created by Yamada on 29-5-2023.
//

#ifndef KMGDEV1_01_MATHF_H
#define KMGDEV1_01_MATHF_H

#include "Vector2.h"
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



} // Hiro

#endif //KMGDEV1_01_MATHF_H
