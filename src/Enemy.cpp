#include <iostream>
#include "Enemy.h"
Enemy::Enemy() : Entity() {
    // set position here (or let another class handle that?)

}

void Enemy::update(float _delta) {

    Entity::update(_delta);
    sprite->move(0.f, 30.f * _delta);
    animate(_delta);
}

void Enemy::initializeTexture() {
    Entity::initializeTexture();

    cellSize = sf::Vector2i(int(texture->getSize().x) / cellCount, int(texture->getSize().y));
    sf::IntRect r(cellSize.x * currentCell, 0, cellSize.x, cellSize.y);
    sprite->setTextureRect(r);
}

std::string Enemy::getTexturePath() {
    return texturePath;
}

void Enemy::animate(float _delta) {
    animationDelta += _delta;
    float rate = 1.f/ float(frameRate);
    if (animationDelta < rate) {

        return;
    }

    currentCell < cellCount - 1 ? currentCell += 1 : currentCell = 0;

    sf::IntRect r(cellSize.x * currentCell, 0, cellSize.x, cellSize.y);
    sprite->setTextureRect(r);
    animationDelta = 0.f;
}

