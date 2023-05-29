//
// Created by Yamada on 28-5-2023.
//
#include "Rigidbody.h"
#include <iostream>

namespace Hiro {
    Rigidbody::Rigidbody() : mass(1.0f), friction(.5f) {}

    Rigidbody::Rigidbody(float _mass, float _friction) : mass(_mass), friction(_friction){}

    void Rigidbody::addForce(Vector2<float> _force) {

        Vector2<float> acceleration = Vector2<float>(_force.x / mass, _force.y / mass);
        velocity += acceleration;

        //TODO: implement Vector2.clampMagnitude
        /*if (velocity.sqrMagnitude() > powf(maxVelocity, 2)) {
             velocity.clampMagnitude(maxVelocity);
        }*/

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
        addForce(f);
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


}
