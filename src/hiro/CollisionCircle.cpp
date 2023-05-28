//
// Created by Yamada on 28-5-2023.
//

#include "CollisionCircle.h"
namespace Hiro {

    CollisionCircle::CollisionCircle() : localPosition(Hiro::V2_ZERO<float>), radius(1.0f) {}
    CollisionCircle::CollisionCircle(Vector2<float> _localPosition, float _radius) : localPosition(_localPosition), radius(_radius) {}
    CollisionCircle::CollisionCircle(float _localX, float _localY, float _radius) : localPosition(_localX, _localY), radius(_radius) {}

    Vector2<float> CollisionCircle::getLocalPosition() {
        return localPosition;
    }

    bool CollisionCircle::isColliding(CollisionShape &_collisionShape) {
        Vector2 delta = _collisionShape.getLocalPosition() - getLocalPosition();
        /*float d = delta.sqrMagnitude() - pow(_collisionShape.radius + radius, 2);
        if (d <= 0.0f) {
            return true;
        }*/
        return false;
    }

}