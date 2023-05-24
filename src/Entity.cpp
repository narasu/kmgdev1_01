#include "Entity.h"

Entity::Entity() {
    texture = new sf::Texture();
    sprite = new sf::Sprite();
}

Entity::~Entity() {
    delete(texture);
    delete(sprite);
}

void Entity::update(float _delta) {

}

sf::Sprite Entity::getSprite() {
    return *sprite;
}

void Entity::initializeTexture() {
    if (!texture->loadFromFile(getTexturePath())) {
        return;
    }
    sprite->setTexture(*texture);
}
