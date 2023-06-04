// Base for sprite objects that need to be updated each frame
// Intended for other classes to inherit from, not to instantiate by itself

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
    virtual void update(float _delta) = 0;
    virtual sf::Sprite& getSprite();
    virtual Vector2<float> getPosition();
    virtual bool isDestroyed(); //gets called each frame by EntityManager which handles the actual destroying
protected:
    std::unique_ptr<sf::Sprite> sprite;
    Vector2<float> position = V2_ZERO<float>;
    bool destroyed = false;
};