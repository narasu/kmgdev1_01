#include "Entity.h"
#include "hiro/Rigidbody.h"

#pragma once

class PhysicsEntity : public Entity {
public:
    PhysicsEntity(sf::Texture *_texture, float _mass, float _friction);
    ~PhysicsEntity() override;
    void update(float _delta) override;
protected:
    Hiro::Rigidbody* rigidbody;
    //Hiro::CollisionShape* collisionShape;
};