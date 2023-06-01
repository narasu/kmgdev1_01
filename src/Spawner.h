#include "Enemy.h"
#pragma once

class Spawner {
public:
    Spawner();
    Spawner(int _viewportWidth, float _spawnInterval);
    bool updateTimer(float _delta);
    std::shared_ptr<Enemy> spawnEnemy(const sf::Texture &_texture, float _playerX);
private:
    int viewportWidth;
    float spawnInterval;
    float time = .0f;
    float lastSpawnPosition = .0f;
    bool biasTriggered = false;
};