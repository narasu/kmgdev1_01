#include <iostream>
#include <SFML/Graphics.hpp>
#include "abstract/GameEntity.h"

#pragma once

class Player : public GameEntity {
private:
    std::string texturePath = "assets/sprites/player.png";
    float speed = 5.f;
protected:
    std::string getTexturePath() override;

public:
    Player();
    void handleMovement();
};
