#include "Hiro.h"
#include <iostream>

namespace Hiro {
    Rigidbody::Rigidbody() : mass(1.0f) {}

    Rigidbody::Rigidbody(float _mass) : mass(_mass) {}

    void Rigidbody::addForce(Vector2<float> _force) {
        friction = _force.sqrMagnitude() > 0 ? _force.magnitude() : friction;
        velocity += _force / mass;
    }
    void Rigidbody::addForce(float _forceX, float _forceY) {
        addForce(Vector2<float>(_forceX, _forceY));
    }

    void Rigidbody::applyFriction() {
        if (friction == .0f) {
            return;
        }
        Vector2<float> oppositeDirection = -(velocity.normalized());
        Vector2<float> f;
        if (pow(friction, 2) <= velocity.sqrMagnitude()) {
            f = oppositeDirection * friction;
        }
        else {
            f = -velocity;
        }
        addForce(f * frictionMult);
    }

    float Rigidbody::getFriction() {
        return friction;
    }

    Vector2<float> Rigidbody::getVelocity() {
        return velocity;
    }
    void Rigidbody::setVelocity(Vector2<float> _velocity) {
        velocity = _velocity;
    }

    void Rigidbody::setVelocity(float _xVel, float _yVel) {
        velocity.x = _xVel;
        velocity.y = _yVel;
    }

    void Rigidbody::setFrictionMult(float _frictionMult) {
        frictionMult = _frictionMult;
    }


}
