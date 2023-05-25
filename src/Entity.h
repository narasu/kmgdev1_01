#include <SFML/Graphics.hpp>
#pragma once

class Entity  {
public:
    //Entity();
    explicit Entity(sf::Texture* _texture);
    Entity(const Entity& _entity); //copy constructor
    Entity& operator=(const Entity& _entity); //assignment operator
    virtual ~Entity();
    virtual void update(float _delta) = 0;
    virtual sf::Sprite getSprite();
protected:
    sf::Sprite* sprite;
};