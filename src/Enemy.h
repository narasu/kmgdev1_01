#include "Entity.h"
#include "Animator.h"
#pragma once

class Enemy : public Entity {
public:
    explicit Enemy(sf::Texture* _texture);
    void update(float _delta) override;
private:
    Animator animator;
};