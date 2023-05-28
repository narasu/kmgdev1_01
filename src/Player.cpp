#include <iostream>
#include "Player.h"

Player::Player(sf::Texture *_texture) : PhysicsEntity(_texture, 5.0f, 76.0f) {
    position = Hiro::Vector2<float>(155.f, 145.f);
}

void Player::update(float _delta) {

    int direction = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction-=1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction+=1;
    }

    rigidbody->addForce(Hiro::Vector2<float>(float(direction) * moveSpeed, .0f));
    rigidbody->applyFriction();
    position += rigidbody->getVelocity().toSFML() * _delta;
    //sprite->move(rigidbody->getVelocity().toSFML() * _delta);
    PhysicsEntity::update(_delta);
    std::cout << "velocity:" << rigidbody->getVelocity() << ". position: " << position << std::endl;
}

Player::~Player() {
    delete rigidbody;
    rigidbody = nullptr;
}
