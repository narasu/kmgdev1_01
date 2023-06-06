#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(const sf::Texture &_texture, float _mass, float _frictionMult, Rect<float> _localBounds) : BaseEntity(_texture), bounds(_localBounds)  {
    rigidbody = std::make_unique<Rigidbody>(_mass, _frictionMult);
}

PhysicsEntity::PhysicsEntity(const PhysicsEntity &_entity) : BaseEntity(_entity) {
    if (this == &_entity) {
        return;
    }
    rigidbody = std::make_unique<Rigidbody>(*_entity.rigidbody);
}

PhysicsEntity &PhysicsEntity::operator=(const PhysicsEntity &_entity) {
    if (this == &_entity) {
        return *this;
    }
    sprite = std::make_unique<sf::Sprite>(*_entity.sprite);
    rigidbody = std::make_unique<Rigidbody>(*_entity.rigidbody);
    return *this;
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


