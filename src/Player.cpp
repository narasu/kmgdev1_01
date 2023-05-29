#include <iostream>
#include "Player.h"

Player::Player(sf::Texture *_texture) : PhysicsEntity(_texture, 5.0f, 76.0f) {
    position = Vector2<float>(155.f, 145.f);
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

Player::~Player() {
    delete rigidbody;
    rigidbody = nullptr;
}
