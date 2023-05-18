#include <SFML/Graphics.hpp>
#pragma once

class IEntity {
public:
    virtual void update() = 0;
    virtual sf::Sprite getSprite() = 0;
};