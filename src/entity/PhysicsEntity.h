#include "Entity.h"


#pragma once

class PhysicsEntity : public Entity {
public:
    PhysicsEntity(const sf::Texture *_texture, float _mass, float _friction);
    ~PhysicsEntity() override;
    void update(float _delta) override;

protected:
    Rigidbody* rigidbody;

    //CollisionShape* collisionShape;
};