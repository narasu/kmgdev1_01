#include <iostream>
#include "Player.h"
#include "../GameData.h"

Player::Player(const sf::Texture &_texture, Rect<float> _localBounds) : PhysicsEntity(_texture, 10.0f, 0.99f, _localBounds) {
    position = PLAYER_START;
    health = START_HEALTH;
    moveSpeed = PLAYER_SPEED;
}

void Player::update(float _delta) {
    float direction = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction-=1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction+=1;
    }

    //prevent player moving off screen
    if (rigidbody->getVelocity().x < 0 && position.x <= 0) {
        rigidbody->setVelocity(V2_ZERO<float>);
        position.x=0;
    }
    else if (rigidbody->getVelocity().x > 0 && position.x >= VIEWPORT_WIDTH - bounds.w) {
        rigidbody->setVelocity(V2_ZERO<float>);
        position.x= VIEWPORT_WIDTH - bounds.w;
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

