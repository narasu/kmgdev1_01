// Component for physics objects which handles force calculations

#include "Hiro.h"
#pragma once

namespace Hiro {
    class Rigidbody {
    public:
        Rigidbody();
        Rigidbody(float _mass, float _friction);
        void addForce(Vector2<float> _force);
        void addForce(float _forceX, float _forceY);
        Vector2<float> getVelocity();
        void setVelocity(Vector2<float> _velocity);
        void setVelocity(float _xVel, float _yVel);
        float getFriction();
        void applyFriction();
    private:
        Vector2<float> velocity = V2_ZERO<float>;
        float maxVelocity = 270.0f;
        float mass;
        float friction;
    };
}
