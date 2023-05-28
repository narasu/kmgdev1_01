#include <iostream>
#include "Enemy.h"


Enemy::Enemy(sf::Texture *_texture) : PhysicsEntity(_texture, 5.0f, 0.9f) {
    int cellCount = 2;
    animator = Animator(*sprite, int(_texture->getSize().x) / cellCount, int(_texture->getSize().y), cellCount, 2);
}

void Enemy::update(float _delta) {
    animator.animate(*sprite, _delta);
    rigidbody->addForce(.0f, 0.981f);
    sprite->move(rigidbody->getVelocity().toSFML() * _delta);
    PhysicsEntity::update(_delta);
}

