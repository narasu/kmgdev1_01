#include "CollisionShape.h"
namespace Hiro {

    CollisionShape::CollisionShape() : localPosition(.0f, .0f), radius(1.0f) {}
    CollisionShape::CollisionShape(Vector2<float> _localPosition, float _radius) : localPosition(_localPosition), radius(_radius) {}
    CollisionShape::CollisionShape(float _localX, float _localY, float _radius) : localPosition(_localX, _localY), radius(_radius) {}

    bool CollisionShape::isColliding(CollisionShape &_collisionShape) {
        Vector2 delta = _collisionShape.localPosition - localPosition;
        float d = delta.sqrMagnitude() - pow(_collisionShape.radius + radius, 2);
        if (d <= 0.0f) {
            return true;

        }
        return false;
    }

}
