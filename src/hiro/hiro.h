#ifndef KMGDEV1_01_HIRO_H
#define KMGDEV1_01_HIRO_H
#pragma once

namespace Hiro {
    class Mathf;
    template <typename T>
    struct Vector2;
    template <typename T>
    struct AABB;

    struct Vertex;
    struct Edge;
    struct Triangle;

    struct CollisionData;
    class CollisionShape;
    class CollisionTriangle;
    class Rigidbody;
}

#include "Mathf.h"
#include "Vector2.h"
#include "AABB.h"
#include "Vertex.h"
#include "Edge.h"
#include "Triangle.h"
#include "CollisionData.h"
#include "CollisionShape.h"
#include "CollisionTriangle.h"
#include "Rigidbody.h"

#endif //KMGDEV1_01_HIRO_H
