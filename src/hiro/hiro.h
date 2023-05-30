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
    struct Polygon;

    struct CollisionData;
    class CollisionShape;
    class CollisionPolygon;
    class Rigidbody;
}

#include "Mathf.h"
#include "Vector2.h"
#include "AABB.h"
#include "Vertex.h"
#include "Edge.h"
#include "Polygon.h"
#include "CollisionData.h"
#include "CollisionShape.h"
#include "CollisionPolygon.h"
#include "Rigidbody.h"

#endif //KMGDEV1_01_HIRO_H
