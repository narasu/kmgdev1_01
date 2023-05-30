#include <cmath>
#include <iostream>
#include "Enemy.h"


Enemy::Enemy(sf::Texture *_texture, Vector2<float> _startPosition) : PhysicsEntity(_texture, 4.0f, 999.0f) {
    position = _startPosition;
    int cellCount = 2;
    animator = Animator(*sprite, static_cast<int>(_texture->getSize().x) / cellCount, static_cast<int>(_texture->getSize().y), cellCount, 2);
    //rigidbody->addForce(.0f, 13.0f);
}

Enemy::Enemy(sf::Texture *_texture, float _startX, float _startY) :
    Enemy(_texture, Vector2<float>(_startX, _startY)) {}

void Enemy::update(float _delta) {
    //animate the texture
    animator.animate(*sprite, _delta);

    //note: adjusting t and amplitude will not have a 1:1 effect in-game as it's a force scalar and not a position
    //force.t will affect position.amplitude and force.amplitude will affect position.t
    float t = position.y * 0.25f;
    float amplitude = 15.0f;
    float x = std::cos(t) * amplitude;

    rigidbody->addForce(x, 15.0f);
    PhysicsEntity::update(_delta);
}