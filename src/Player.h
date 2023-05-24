#include "Entity.h"
#pragma once

class Player : public Entity {
public:
    Player();
    ~Player();
    void initializeTexture() override;
    void update(float _delta) override;
protected:
    std::string getTexturePath() override;
private:
    std::string texturePath = "assets/sprites/player.png";
    float moveSpeed = 150.f;

};
