#include <iostream>
#include "Enemy.h"


Enemy::Enemy(sf::Texture *_texture) : Entity(_texture) {
    int cellCount = 2;
    animator = Animator(*sprite, int(_texture->getSize().x) / cellCount, int(_texture->getSize().y), cellCount, 2);
}

void Enemy::update(float _delta) {
    sprite->move(0.f, 30.f * _delta);
    animator.animate(*sprite, _delta);
}

