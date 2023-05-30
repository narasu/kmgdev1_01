#include "Entity.h"


#pragma once
using namespace Hiro;
class PhysicsEntity : public Entity {
public:
    PhysicsEntity(const sf::Texture *_texture, float _mass, float _friction);
    ~PhysicsEntity() override;
    void update(float _delta) override;
    Vector2<float> getPosition();
protected:
    Rigidbody* rigidbody;
    Vector2<float> position = V2_ZERO<float>;
    //CollisionShape* collisionShape;
};