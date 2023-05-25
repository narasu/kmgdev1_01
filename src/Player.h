#include "Entity.h"
#pragma once

class Player : public Entity {
public:
    explicit Player(sf::Texture *_texture);
    void update(float _delta) override;
private:
    float moveSpeed = 150.f;

};
