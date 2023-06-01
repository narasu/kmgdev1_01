#include "Entity.h"
#include "PhysicsEntity.h"


PhysicsEntity::PhysicsEntity(const sf::Texture &_texture, float _mass, float _friction, Rect<float> _localBounds) : Entity(_texture), bounds(_localBounds)  {
    rigidbody = new Rigidbody(_mass, _friction);
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

    Entity::update(_delta);
}

