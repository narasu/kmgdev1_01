#include <iostream>
#include "Enemy.h"
Enemy::Enemy() : Entity() {
    // set position here (or let another class handle that?)
}

void Enemy::initializeTexture() {
    Entity::initializeTexture();

    animator = new Animator(*sprite, int(texture->getSize().x) / 2, int(texture->getSize().y), 2, 2);
}

void Enemy::update(float _delta) {

    Entity::update(_delta);
    sprite->move(0.f, 30.f * _delta);
    if (animator != nullptr) {
        animator->animate(*sprite, _delta);
    }
}

Enemy::~Enemy() {
    delete animator;
}

std::string Enemy::getTexturePath() {
    return texturePath;
}