#include "Entity.h"
#include "hiro/Rigidbody.h"
#include "hiro/CollisionShape.h"

#pragma once

class Player : public Entity {
public:
    explicit Player(sf::Texture *_texture);
    ~Player() override;
    void update(float _delta) override;
private:
    float moveSpeed = 150.f;
    Hiro::Rigidbody* rigidbody;
    //Hiro::CollisionShape* collisionShape;
};
