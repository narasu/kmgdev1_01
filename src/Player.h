#include "entity/PhysicsEntity.h"

#pragma once

class Player : public PhysicsEntity {
public:
    explicit Player(const sf::Texture &_texture, Rect<float> _localBounds);
    void update(float _delta) override;
    void onCollision() override;
    int getHealth();
private:
    float moveSpeed = 150.f;
    int health;

};
