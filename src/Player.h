#include "entity/Entity.h"

#pragma once

class Player : public PhysicsEntity {
public:
    explicit Player(const sf::Texture *_texture);
    void update(float _delta) override;
private:
    float moveSpeed = 150.f;
};
