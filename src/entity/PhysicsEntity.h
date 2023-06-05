// Base for entities which have physics
// Intended for other classes to inherit from, not to instantiate by itself


//TODO: change rigidbody raw ptr to smart ptr
#include "BaseEntity.h"
#pragma once

class PhysicsEntity : public BaseEntity {
public:
    PhysicsEntity(const sf::Texture &_texture, float _mass, Rect<float> _localBounds);
    ~PhysicsEntity() override;
    void update(float _delta) override;
    Rect<float> getBoundsGlobal();
    virtual void onCollision() = 0;
protected:
    Rigidbody* rigidbody;
    Rect<float> bounds;

};