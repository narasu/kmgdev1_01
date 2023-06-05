#include "BaseEntity.h"
#pragma once

class Grass : public BaseEntity {
public:
    Grass(const sf::Texture &_texture, Vector2<float> _startPosition, float _speedY);
    Grass(const sf::Texture &_texture, float _posX, float _posY, float _speedY);
    void update(float _delta) override;
    void setSpeedY(float _speed);
private:
    float speedY;
};