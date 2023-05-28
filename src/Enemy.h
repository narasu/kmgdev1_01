#include "PhysicsEntity.h"
#include "Animator.h"
#pragma once

class Enemy : public PhysicsEntity {
public:
    Enemy(sf::Texture* _texture, Hiro::Vector2<float> _startPosition);
    Enemy(sf::Texture* _texture, float _startX, float _startY);
    void update(float _delta) override;
private:
    Animator animator;
};