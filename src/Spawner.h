#include "Enemy.h"
#pragma once

class Spawner {
public:
    Spawner();
    explicit Spawner(float _spawnInterval);
    bool intervalReached(float _delta);
    std::unique_ptr<Enemy> spawnEnemy(const sf::Texture &_texture, const Rect<float> _bounds, float _playerX);
private:
    float spawnInterval;
    float time = .0f;
    float lastSpawnPosition = .0f;
    bool biasTriggered = false;
};