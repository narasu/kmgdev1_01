#include "PhysicsEntity.h"
#include "Animator.h"
#pragma once

class Enemy : public PhysicsEntity {
public:
    Enemy(const sf::Texture &_texture, Vector2<float> _startPosition, Rect<float> _localBounds, float _yForce);
    Enemy(const sf::Texture &_texture, float _startX, float _startY, Rect<float> _localBounds, float _yForce);
    void update(float _delta) override;
    void onCollision() override;
    bool isOutOfBounds();
private:
    Animator animator;
    bool outOfBounds = false;
    float yForce;
    float startX;
    float tSin = .0f;
};