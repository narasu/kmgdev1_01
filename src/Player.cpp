#include <iostream>
#include "Player.h"
#include "GameData.h"

Player::Player(const sf::Texture &_texture, Rect<float> _localBounds) : PhysicsEntity(_texture, 5.0f, 145.0f, _localBounds) {
    position = PLAYER_START;
    health = HEALTH;
}

void Player::update(float _delta) {
    float direction = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction-=1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction+=1;
    }
    rigidbody->addForce(moveSpeed * direction, .0f);
    PhysicsEntity::update(_delta);
}

void Player::onCollision() {
    health--;
    if (health <= 0) {
        destroyed = true;
    }
}

int Player::getHealth() {
    return health;
}
