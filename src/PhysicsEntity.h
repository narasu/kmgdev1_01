#include "Entity.h"
#include "hiro/hiro.h"

#pragma once
using namespace Hiro;
class PhysicsEntity : public Entity {
public:
    PhysicsEntity(sf::Texture *_texture, float _mass, float _friction);
    ~PhysicsEntity() override;
    void update(float _delta) override;
    Vector2<float> getPosition();
protected:
    Rigidbody* rigidbody;
    Vector2<float> position = V2_ZERO<float>;
    float maxVelocityMagnitude = .0f;
    //CollisionShape* collisionShape;
};