#include "Vector2.h"
#include "CollisionShape.h"
#pragma once

namespace Hiro {
    class Rigidbody {
    public:
        Rigidbody();
        Rigidbody(float _mass, float _friction);
        void addForce(Vector2<float> _force);
        void addForce(float _forceX, float _forceY);
        Vector2<float> getVelocity();
        void applyFriction();
    private:
        Vector2<float> velocity = Vector2<float>(.0f,.0f);
        float mass;
        float friction;
    };
}
