#include <iostream>
#include "BaseEntity.h"

BaseEntity::BaseEntity(const sf::Texture &_texture)  {
    sprite = std::make_unique<sf::Sprite>();
    sprite->setTexture(_texture);
}

BaseEntity::BaseEntity(const BaseEntity &_entity) {
    if (this == &_entity) {
        return;
    }
    sprite = std::make_unique<sf::Sprite>(*_entity.sprite);
}

BaseEntity &BaseEntity::operator=(const BaseEntity &_entity) {
    if (this == &_entity) {
        return *this;
    }
    sprite = std::make_unique<sf::Sprite>(*_entity.sprite);
    return *this;
}

sf::Sprite& BaseEntity::getSprite() {
    return *sprite;
}

Vector2<float> BaseEntity::getPosition() {
    return position;
}

bool BaseEntity::isDestroyed() {
    return destroyed;
}

