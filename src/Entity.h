#include <SFML/Graphics.hpp>
#pragma once

class Entity  {
public:
    Entity();
    virtual ~Entity();
    virtual void update(float _delta);
    virtual sf::Sprite getSprite();
    virtual void initializeTexture();
protected:
    virtual std::string getTexturePath() = 0;
    sf::Texture* texture;
    sf::Sprite* sprite;
};