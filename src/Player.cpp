#include <iostream>
#include "Player.h"

Player::Player() : Entity() {
    sprite->setPosition(155.f, 145.f);
}

void Player::initializeTexture() {
    Entity::initializeTexture();
}

void Player::update(float _delta) {
    Entity::update(_delta);
    int direction = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction--;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction++;
    }
    sprite->move(direction * moveSpeed * _delta, 0.f);
}

Player::~Player() {
    std::cout << "player destructor" << std::endl;
}

std::string Player::getTexturePath() {
    return texturePath;
}

