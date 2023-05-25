#include <iostream>
#include "Enemy.h"


Enemy::Enemy(sf::Texture *_texture) : Entity(_texture) {
    animator = Animator(*sprite, int(_texture->getSize().x) / 2, int(_texture->getSize().y), 2, 2);
}

void Enemy::update(float _delta) {
    sprite->move(0.f, 30.f * _delta);
    animator.animate(*sprite, _delta);
}

