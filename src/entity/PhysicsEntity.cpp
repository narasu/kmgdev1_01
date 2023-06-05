#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(const sf::Texture &_texture, float _mass, Rect<float> _localBounds) : BaseEntity(_texture), bounds(_localBounds)  {
    rigidbody = new Rigidbody(_mass);
}
PhysicsEntity::~PhysicsEntity() {
    delete rigidbody;
    rigidbody = nullptr;
}

void PhysicsEntity::update(float _delta) {
    rigidbody->applyFriction();
    position += rigidbody->getVelocity() * _delta;

    //reset velocity to 0 if its magnitude is below 0.01
    if (rigidbody->getVelocity().sqrMagnitude() < 0.0001f) {
        rigidbody->setVelocity(V2_ZERO<float>);
    }

    // round to whole numbers to prevent sub-pixel rendering
    // does this make everything jittery and also slightly inaccurate? yes
    // but it really sells the arcade aesthetic, so it's here to stay
    sprite->setPosition(roundf(position.x), roundf(position.y));
}

Rect<float> PhysicsEntity::getBoundsGlobal() {
    return Rect<float>(bounds.x + position.x, bounds.y + position.y, bounds.w, bounds.h);
}