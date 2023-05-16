#include <iostream>
#include "GameEntity.h"

GameEntity::GameEntity() {
    texture = new sf::Texture();
}

GameEntity::~GameEntity() {
    delete(texture);
}

void GameEntity::initializeTexture() {
    if (!texture->loadFromFile(getTexturePath())) {
        std::cout << "Could not load texture at " << getTexturePath() << std::endl;
        return;
    }
    setTexture(*texture);
}
