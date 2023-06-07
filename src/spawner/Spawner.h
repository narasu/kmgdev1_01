#include "../managers/Managers.h"
#include "../entity/Enemy.h"
#include "../entity/Grass.h"
#include "SpawnType.h"
#include "../GameData.h"

#pragma once

class Spawner {
public:
    Spawner(std::shared_ptr<TextureManager> _textureManager, std::shared_ptr<EntityManager> _entityManager);
    Spawner(const Spawner &_spawner);
    Spawner& operator=(const Spawner &_spawner);
    void update(int _stage, float _delta, float _playerX = -100.0f);
    void spawnEnemy(int _stage, int _count, float _playerX);
    void spawnGrass(int _stage, int _count);
    void setSpawnInterval(SpawnType _type, float _seconds) { spawnIntervals[_type] = _seconds; }
    void setTimerActive(SpawnType _type, bool _active);
    bool isEnemySpawned() { return enemySpawned; }
    void spawnCallback() { enemySpawned = false; }
private:
    bool intervalReached(SpawnType _type);
    float generateRandomPosition(float _last, float _offset);
    void keepWithinBounds(float &_position);
    std::shared_ptr<TextureManager> textureManager;
    std::shared_ptr<EntityManager> entityManager;
    std::map<SpawnType, float> spawnIntervals = {{SpawnType::ENEMY, ENEMY_SPAWN_INTERVAL[0]}, {SpawnType::GRASS, GRASS_SPAWN_INTERVAL[0]}};
    std::map<SpawnType, float> time = {{SpawnType::ENEMY, .0f}, {SpawnType::GRASS, GRASS_SPAWN_INTERVAL[0]}}; //initialize grass timer at its interval to spawn some grass immediately
    std::map<SpawnType, bool> timerActive = {{SpawnType::ENEMY, false}, {SpawnType::GRASS, false}};
    std::map<SpawnType, float> lastSpawn = {{SpawnType::ENEMY, .0f}, {SpawnType::GRASS, .0f}};
    bool biasTriggered = false;
    int lastEnemy = 0;
    bool enemySpawned = false;
};