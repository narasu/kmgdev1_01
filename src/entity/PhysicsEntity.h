// Base for entities which have physics
// Intended for other classes to inherit from, not to instantiate by itself

#include "BaseEntity.h"
#pragma once

class PhysicsEntity : public BaseEntity {
public:
    PhysicsEntity(const sf::Texture &_texture, float _mass, float _frictionMult, Rect<float> _localBounds);
    PhysicsEntity(const PhysicsEntity& _entity); //copy constructor
    PhysicsEntity& operator=(const PhysicsEntity& _entity); //assignment operator
    ~PhysicsEntity() override = default;
    void update(float _delta) override;
    Rect<float> getBoundsGlobal();
    virtual void onCollision() = 0;
protected:
    std::unique_ptr<Rigidbody> rigidbody;
    Rect<float> bounds;

};