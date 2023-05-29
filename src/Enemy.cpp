#include <cmath>
#include <iostream>
#include "Enemy.h"
#include "hiro/Mathf.h"


Enemy::Enemy(sf::Texture *_texture, Vector2<float> _startPosition) : PhysicsEntity(_texture, 1.0f, .0f) {
    position = _startPosition;
    int cellCount = 2;
    animator = Animator(*sprite, static_cast<int>(_texture->getSize().x) / cellCount, static_cast<int>(_texture->getSize().y), cellCount, 2);
    rigidbody->addForce(.0f, 13.0f);
}

Enemy::Enemy(sf::Texture *_texture, float _startX, float _startY) :
    Enemy(_texture, Vector2<float>(_startX, _startY)) {}

void Enemy::update(float _delta) {
    //animate the texture
    animator.animate(*sprite, _delta);

    //horizontal movement is based on a cosine shape.
    float t = position.y * 0.25f;
    float dir = std::cos(t);
    float amplitude = 1.0f;
    float forceScalar = dir * amplitude;

    rigidbody->addForce(forceScalar, .0f);
    PhysicsEntity::update(_delta);
}