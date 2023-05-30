//
// Created by Yamada on 29-5-2023.
//

#ifndef KMGDEV1_01_HIRO_H
#define KMGDEV1_01_HIRO_H
#pragma once

namespace Hiro {
    class Mathf;
    template <typename T>
    struct Vector2;
    template <typename T>
    struct AABB;

    struct CollisionData;
    class CollisionShape;
    class Rigidbody;
}

#include "Mathf.h"
#include "Vector2.h"
#include "AABB.h"
#include "CollisionData.h"
#include "CollisionShape.h"
#include "Rigidbody.h"

#endif //KMGDEV1_01_HIRO_H
