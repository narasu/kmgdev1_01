#include "entity/Entity.h"
#include "Animator.h"
#pragma once

class Enemy : public PhysicsEntity {
public:
    Enemy(const sf::Texture &_texture, Vector2<float> _startPosition);
    Enemy(const sf::Texture &_texture, float _startX, float _startY);
    void update(float _delta) override;
private:
    Animator animator;
};