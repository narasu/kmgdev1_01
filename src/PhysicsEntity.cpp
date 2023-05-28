//
// Created by Yamada on 28-5-2023.
//

#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(sf::Texture *_texture, float _mass, float _friction) : Entity(_texture) {
    rigidbody = new Hiro::Rigidbody(_mass, _friction);
    // collisionShape = new collisionshape
}

PhysicsEntity::~PhysicsEntity() {
    delete rigidbody;
    rigidbody = nullptr;
    //delete collisionShape
}

void PhysicsEntity::update(float _delta) {
    //reset velocity to 0 if its magnitude is below 0.01
    if (rigidbody->getVelocity().sqrMagnitude() < 0.0001f) {
        rigidbody->setVelocity(.0f, .0f);
    }

    // render sprite at nearest round values to prevent sub-pixel displacement
    // does this make everything super jittery? yes
    // it also sells the arcade aesthetic beautifully, so it's here to stay
    sprite->setPosition(roundf(position.x), roundf(position.y));
}

