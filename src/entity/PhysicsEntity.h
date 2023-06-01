// Base for entities which have physics
// Intended for other classes to inherit from, not to instantiate by itself

#include "Entity.h"
#pragma once

class PhysicsEntity : public Entity {
public:
    PhysicsEntity(const sf::Texture &_texture, float _mass, float _friction, Rect<float> _localBounds);
    ~PhysicsEntity() override;
    void update(float _delta) override;

protected:
    Rigidbody* rigidbody;
    Rect<float> bounds;
};