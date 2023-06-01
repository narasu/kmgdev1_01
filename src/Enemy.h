#include "entity/Entity.h"
#include "Animator.h"
#pragma once

class Enemy : public PhysicsEntity {
public:
    Enemy(const sf::Texture &_texture, Vector2<float> _startPosition, Rect<float> _localBounds);
    Enemy(const sf::Texture &_texture, float _startX, float _startY, Rect<float> _localBounds);
    void update(float _delta) override;
    void onCollision() override;
private:
    Animator animator;
};