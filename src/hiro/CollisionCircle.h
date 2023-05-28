#include "CollisionShape.h"
#pragma once;

namespace Hiro {

    class CollisionCircle : public CollisionShape {
    public:
        CollisionCircle();
        CollisionCircle(Vector2<float> _localPosition, float _radius = 1.0f);
        CollisionCircle(float _localX, float _localY, float _radius = 1.0f);
        Vector2<float> getLocalPosition() override;
        bool isColliding(CollisionShape& _collisionShape) override;

    private:
        Vector2<float> localPosition;
        float radius;
    };

} // Hiro
