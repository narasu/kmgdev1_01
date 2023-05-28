//
// Created by Yamada on 28-5-2023.
//
#include "Rigidbody.h"
#include <iostream>

namespace Hiro {
    Rigidbody::Rigidbody() : mass(1.0f), friction(.5f) {}

    Rigidbody::Rigidbody(float _mass, float _friction) : mass(_mass), friction(_friction){}

    // addForce(10, 10)
    void Rigidbody::addForce(Vector2<float> _force) {
        Vector2<float> acceleration = Vector2<float>(_force.x / mass, _force.y / mass);
        velocity += acceleration;
    }
    void Rigidbody::addForce(float _forceX, float _forceY) {
        addForce(Vector2<float>(_forceX, _forceY));
    }

    void Rigidbody::applyFriction() {
        velocity *= friction;
    }

    Vector2<float> Rigidbody::getVelocity() {
        std::cout << velocity << std::endl;
        return velocity;
    }

}
