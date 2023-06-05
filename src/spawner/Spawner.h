#include "../entity/Enemy.h"
#include "../entity/Grass.h"
#include "SpawnType.h"

#pragma once

class Spawner {
public:
    Spawner(float _enemySpawnInterval, float _grassSpawnInterval);
    bool intervalReached(SpawnType _type, float _delta);
    void updateTimer(SpawnType _type, float _delta);
    std::unique_ptr<Enemy> spawnEnemy(const sf::Texture &_texture, Rect<float> _bounds, float _yForce, float _playerX);
    std::unique_ptr<Grass> spawnGrass(const sf::Texture &_texture, float _speedY);
    void setSpawnInterval(SpawnType _type, float _seconds);
private:
    float generateRandomPosition(float &_last, float _offset);
    std::map<SpawnType, float> spawnIntervals = {{SpawnType::ENEMY, .0f}, {SpawnType::GRASS, .0f}};
    std::map<SpawnType, float> time = {{SpawnType::ENEMY, .0f}, {SpawnType::GRASS, .0f}};
    std::map<SpawnType, float> lastSpawn = {{SpawnType::ENEMY, .0f}, {SpawnType::GRASS, .0f}};
    bool biasTriggered = false;
};