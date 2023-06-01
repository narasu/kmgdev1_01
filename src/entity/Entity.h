// Base for objects in the game that require sprite logic
// Intended for other classes to inherit from, not to instantiate by itself

#ifndef KMGDEV1_01_ENTITY_H
#define KMGDEV1_01_ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "../hiro/Hiro.h"
#pragma once
using namespace Hiro;
class Entity  {
public:
    explicit Entity(const sf::Texture &_texture);
    Entity(const Entity& _entity); //copy constructor
    Entity& operator=(const Entity& _entity); //assignment operator
    virtual ~Entity() = default;
    virtual void update(float _delta);
    virtual sf::Sprite& getSprite();
    virtual Vector2<float> getPosition();
    virtual bool isDestroyed() = 0;
protected:
    std::unique_ptr<sf::Sprite> sprite;
    Vector2<float> position = V2_ZERO<float>;
    Vector2<float> origin;
    bool destroyed = false;
};

class PhysicsEntity;

#include "PhysicsEntity.h"

#endif