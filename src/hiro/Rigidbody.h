// Component for physics objects which handles force calculations

#include "Hiro.h"
#pragma once

namespace Hiro {
    class Rigidbody {
    public:
        Rigidbody() : mass(1.0f), frictionMult(1.0f) {}
        Rigidbody(float _mass = 1.0f, float _frictionMult = 1.0f) : mass(_mass), frictionMult(_frictionMult) {}
        void addForce(Vector2<float> _force);
        void addForce(float _forceX, float _forceY);
        void applyFriction();
        Vector2<float> getVelocity() { return velocity; }
        void setVelocity(Vector2<float> _velocity) { velocity = _velocity; }
        void setVelocity(float _xVel, float _yVel) { velocity = Vector2<float>(_xVel,_yVel); }
        void setFrictionMult(float _frictionMult) { frictionMult = _frictionMult; }
    private:
        Vector2<float> velocity = V2_ZERO<float>;
        float friction = .0f;
        float mass;
        float frictionMult;
    };
}
