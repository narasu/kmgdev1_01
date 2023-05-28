#include <cmath>
#include <iostream>
#include "Enemy.h"


Enemy::Enemy(sf::Texture *_texture, Hiro::Vector2<float> _startPosition) : PhysicsEntity(_texture, 1.0f, 0.1f) {
    //sprite->setPosition(_startPosition.toSFML());
    position = _startPosition;
    int cellCount = 2;
    animator = Animator(*sprite, static_cast<int>(_texture->getSize().x) / cellCount, static_cast<int>(_texture->getSize().y), cellCount, 2);
}

Enemy::Enemy(sf::Texture *_texture, float _startX, float _startY) :
    Enemy(_texture, Hiro::Vector2<float>(_startX, _startY)) {}

void Enemy::update(float _delta) {
    //animate the texture
    animator.animate(*sprite, _delta);

    //vertical movement is constant
    Hiro::Vector2<float> movement = Hiro::Vector2<float>(0.0f, 15.0f);

    //horizontal movement is handled by forces based on a cosine shape.
    float waveLength = position.y * 0.4f;
    float amplitude = 7.5f;
    float d = std::cos(waveLength) * amplitude;
    rigidbody->addForce(d, .0f);
    rigidbody->applyFriction();
    movement += rigidbody->getVelocity();
    position += movement * _delta;

    PhysicsEntity::update(_delta);
}