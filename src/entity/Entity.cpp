#include <iostream>
#include "Entity.h"

Entity::Entity(const sf::Texture &_texture)  {
    sprite = std::make_unique<sf::Sprite>();
    sprite->setTexture(_texture);
    origin = Hiro::Vector2<float>(sprite->getTextureRect().width*0.5f, sprite->getTextureRect().height*0.5f);
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

void Entity::update(float _delta) {
    // draw sprite so the entity's position represents its center
    // round to whole numbers to prevent sub-pixel positions
    // does this make everything jittery and also slightly inaccurate? yes
    // but it really sells the arcade aesthetic, so it's here to stay
    sprite->setPosition(roundf(position.x - origin.x), roundf(position.y - origin.y));
}

sf::Sprite& Entity::getSprite() {
    return *sprite;
}

Vector2<float> Entity::getPosition() {
    return position;
}

