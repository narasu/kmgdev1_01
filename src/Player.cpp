#include <iostream>
#include "Player.h"

Player::Player(sf::Texture *_texture) : Entity (_texture){
    sprite->setPosition(155.f, 145.f);
    rigidbody = new Hiro::Rigidbody(5.0f, 0.9f);
}

void Player::update(float _delta) {

    int direction = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction-=1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction+=1;
    }

    //technically the movement isn't affected if direction is 0, but it saves some performance by minimizing physics calculations
    if (direction!=0) {
        rigidbody->addForce(Hiro::Vector2<float>(float(direction) * moveSpeed, .0f));
    }
    rigidbody->applyFriction();
    sprite->move(rigidbody->getVelocity().toSFML() * _delta);
}

Player::~Player() {
    delete rigidbody;
    rigidbody = nullptr;
}
