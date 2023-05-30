#ifndef KMGDEV1_01_ENTITY_H
#define KMGDEV1_01_ENTITY_H

#include <SFML/Graphics.hpp>
#include "../hiro/Hiro.h"
#pragma once

class Entity  {
public:
    explicit Entity(sf::Texture* _texture);
    Entity(const Entity& _entity); //copy constructor
    Entity& operator=(const Entity& _entity); //assignment operator
    virtual ~Entity();
    virtual void update(float _delta) = 0;
    virtual sf::Sprite& getSprite();
protected:
    sf::Sprite* sprite;
};

class PhysicsEntity;

#include "PhysicsEntity.h"

#endif