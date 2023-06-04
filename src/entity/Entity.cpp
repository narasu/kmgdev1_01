#include <iostream>
#include "Entity.h"

Entity::Entity(const sf::Texture &_texture)  {
    sprite = std::make_unique<sf::Sprite>();
    sprite->setTexture(_texture);
}

Entity::Entity(const Entity &_entity) {
    if (this == &_entity) {
        return;
    }
    sprite = std::make_unique<sf::Sprite>(*_entity.sprite);
}

Entity &Entity::operator=(const Entity &_entity) {
    if (this == &_entity) {
        return *this;
    }
    sprite = std::make_unique<sf::Sprite>(*_entity.sprite);
    return *this;
}

sf::Sprite& Entity::getSprite() {
    return *sprite;
}

Vector2<float> Entity::getPosition() {
    return position;
}

bool Entity::isDestroyed() {
    return destroyed;
}

