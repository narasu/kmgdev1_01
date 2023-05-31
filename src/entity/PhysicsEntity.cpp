#include "Entity.h"

PhysicsEntity::PhysicsEntity(const sf::Texture *_texture, float _mass, float _friction) : Entity(_texture) {
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

    // draw sprite so the entity's position represents its center
    // render sprite at nearest round values to prevent sub-pixel displacement
    // does this make everything jittery and also slightly inaccurate? yes
    // but it really sells the arcade aesthetic, so it's here to stay
    sprite->setPosition(roundf(position.x - origin.x), roundf(position.y - origin.y));
}

