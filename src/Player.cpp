#include <iostream>
#include "Player.h"

Player::Player(const sf::Texture &_texture, Rect<float> _localBounds) : PhysicsEntity(_texture, 5.0f, 150.0f, _localBounds) {
    position = Vector2<float>(160.f, 155.f);
}

void Player::update(float _delta) {

    int direction = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction-=1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction+=1;
    }

    rigidbody->addForce(moveSpeed * direction, .0f);

    PhysicsEntity::update(_delta);
}