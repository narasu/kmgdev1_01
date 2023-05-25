#include <iostream>
#include "Player.h"

Player::Player(sf::Texture *_texture) : Entity (_texture){
    sprite->setPosition(155.f, 145.f);
}

void Player::update(float _delta) {

    int direction = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction-=1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction+=1;
    }
    sprite->move(float(direction) * moveSpeed * _delta, 0.f);
}