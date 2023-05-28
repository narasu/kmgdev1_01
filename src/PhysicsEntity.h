#include "Entity.h"
#include "hiro/Rigidbody.h"

#pragma once

class PhysicsEntity : public Entity {
public:
    PhysicsEntity(sf::Texture *_texture, float _mass, float _friction);
    ~PhysicsEntity() override;
    void update(float _delta) override;
    Hiro::Vector2<float> getPosition();
protected:
    Hiro::Rigidbody* rigidbody;
    Hiro::Vector2<float> position = Hiro::V2_ZERO<float>;
    //Hiro::CollisionShape* collisionShape;
};