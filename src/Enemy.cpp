#include <cmath>
#include "Enemy.h"


Enemy::Enemy(const sf::Texture &_texture, Vector2<float> _startPosition) : PhysicsEntity(_texture, 4.0f, 999.0f) {
    position = _startPosition;
    int cellCount = 2;
    animator = Animator(*sprite, static_cast<int>(_texture.getSize().x) / cellCount, static_cast<int>(_texture.getSize().y), cellCount, 2);
}

Enemy::Enemy(const sf::Texture &_texture, float _startX, float _startY) :
    Enemy(_texture, Vector2<float>(_startX, _startY)) {}

void Enemy::update(float _delta) {
    //animate the texture
    animator.animate(*sprite, _delta);

    //note: adjusting t and amplitude will not have a 1:1 effect on the localPosition as it's a force scalar
    float t = position.y * 0.25f;
    float amplitude = 20.0f;
    float x = std::cos(t) * amplitude;

    rigidbody->addForce(x, 15.0f);
    PhysicsEntity::update(_delta);
}