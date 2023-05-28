#include "PhysicsEntity.h"
#include "Animator.h"
#pragma once

class Enemy : public PhysicsEntity {
public:
    explicit Enemy(sf::Texture* _texture);
    void update(float _delta) override;
private:
    Animator animator;
};