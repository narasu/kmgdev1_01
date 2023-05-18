#include <iostream>
#include "Entity.h"
#pragma once
Entity::Entity() {
    texture = new sf::Texture();
    sprite = new sf::Sprite();
}

Entity::~Entity() {
    delete(texture);
    delete(sprite);
    std::cout << "Entity destructor" << std::endl;
}

void Entity::update() {

}

sf::Sprite Entity::getSprite() {
    return *sprite;
}
