#include "Hiro.h"
#include <iostream>

namespace Hiro {
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
}
