#ifndef KMGDEV1_01_ENTITY_H
#define KMGDEV1_01_ENTITY_H

#include <SFML/Graphics.hpp>
#include "../hiro/Hiro.h"
#pragma once
using namespace Hiro;
class Entity  {
public:
    explicit Entity(const sf::Texture *_texture);
    Entity(const Entity& _entity); //copy constructor
    Entity& operator=(const Entity& _entity); //assignment operator
    virtual ~Entity();
    virtual void update(float _delta) = 0;
    virtual sf::Sprite& getSprite();
    virtual Vector2<float> getPosition();
protected:
    sf::Sprite* sprite;
    Vector2<float> position = V2_ZERO<float>;
    Vector2<float> origin;
};

class PhysicsEntity;

#include "PhysicsEntity.h"

#endif