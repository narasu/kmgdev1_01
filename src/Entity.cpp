#include "Entity.h"

//Entity::Entity() {
//
//}

Entity::Entity(sf::Texture* _texture)  {
    sprite = new sf::Sprite();
    sprite->setTexture(*_texture);
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
    delete(sprite);
    sprite = nullptr;
}

sf::Sprite Entity::getSprite() {
    return *sprite;
}

/*
void Entity::initializeTexture() {
    if (!texture->loadFromFile(getTexturePath())) {
        return;
    }
    sprite->setTexture(*texture);
}
*/
