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
    // round position to nearest whole number to prevent sub-pixel displacement
    // does this make everything super jittery? yes
    // it also sells the arcade aesthetic beautifully
    // so it's here to stay
    sprite->setPosition(round(sprite->getPosition().x), round(sprite->getPosition().y));
}

