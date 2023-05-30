#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(sf::Texture *_texture, float _mass, float _friction) : Entity(_texture) {
    rigidbody = new Rigidbody(_mass, _friction);
    // collisionShape = new collisionshape
}

PhysicsEntity::~PhysicsEntity() {
    delete rigidbody;
    rigidbody = nullptr;
    //delete collisionShape
}

void PhysicsEntity::update(float _delta) {
    rigidbody->applyFriction();
    position += rigidbody->getVelocity() * _delta;

    //reset velocity to 0 if its magnitude is below 0.01
    if (rigidbody->getVelocity().sqrMagnitude() < 0.0001f) {
        rigidbody->setVelocity(V2_ZERO<float>);
    }

    // render sprite at nearest round values to prevent sub-pixel displacement
    // does this make everything jittery? yes
    // but it really sells the arcade aesthetic, so it's here to stay
    sprite->setPosition(roundf(position.x), roundf(position.y));
}

Vector2<float> PhysicsEntity::getPosition() {
    return position;
}

