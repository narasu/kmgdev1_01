#include "entity/Entity.h"

#pragma once

class Player : public PhysicsEntity {
public:
    explicit Player(sf::Texture *_texture);
    ~Player() override;
    void update(float _delta) override;
private:
    float moveSpeed = 150.f;
};
