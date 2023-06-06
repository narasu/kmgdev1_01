// Component for physics objects which handles force calculations

#include "Hiro.h"
#pragma once

namespace Hiro {
    class Rigidbody {
    public:
        Rigidbody();
        Rigidbody(float _mass = 1.0f, float _frictionMult = 1.0f);
        void addForce(Vector2<float> _force);
        void addForce(float _forceX, float _forceY);
        Vector2<float> getVelocity() { return velocity; }
        void setVelocity(Vector2<float> _velocity);
        void setVelocity(float _xVel, float _yVel);
        void setFrictionMult(float _frictionMult);
        void applyFriction();
    private:
        Vector2<float> velocity = V2_ZERO<float>;
        float friction = .0f;
        float mass;
        float frictionMult;
    };
}
