#include <iostream>
#include "Entity.h"
#include "../hiro/Hiro.h"
#include <cmath>

Entity::Entity(const sf::Texture *_texture)  {
    sprite = new sf::Sprite();
    sprite->setTexture(*_texture);
    origin = Hiro::Vector2<float>(sprite->getTextureRect().width*0.5f, sprite->getTextureRect().height*0.5f);
}

Entity::Entity(const Entity &_entity) {
    if (this == &_entity) {
        return;
    }
    sprite = new sf::Sprite(*_entity.sprite);
}

Entity &Entity::operator=(const Entity &_entity) {
    if (this == &_entity) {
        return *this;
    }
    sprite = new sf::Sprite(*_entity.sprite);
    return *this;
}

Entity::~Entity() {
    delete sprite;
    sprite = nullptr;
}

sf::Sprite& Entity::getSprite() {
    return *sprite;
}

Vector2<float> Entity::getPosition() {
    return position;
}
