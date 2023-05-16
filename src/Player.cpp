#include <iostream>
#include "Player.h"

Player::Player() : GameEntity() {
    initializeTexture();
    setPosition(155, 155);
}

std::string Player::getTexturePath() {
    return texturePath;
}

void Player::handleMovement() {
    int direction = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction--;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction++;
    }
    move(speed * direction, 0.f);
}
