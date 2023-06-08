#include "../managers/Managers.h"
#include "../entity/Enemy.h"
#include "../entity/Grass.h"
#include "../enums/SpawnType.h"
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
    void setTimerActive(SpawnType _type, bool _active);
    void setSpawnInterval(SpawnType _type, float _seconds) { spawnIntervals[_type] = _seconds; }
    bool isEnemySpawned() { return enemySpawned; }
    void spawnCallback() { enemySpawned = false; }
private:
    bool intervalReached(SpawnType _type);
    float generateRandomPosition(float _last, float _offset);
    std::shared_ptr<TextureManager> textureManager;
    std::shared_ptr<EntityManager> entityManager;
    std::map<SpawnType, float> spawnIntervals;
    std::map<SpawnType, float> time;
    std::map<SpawnType, bool> timerActive;
    std::map<SpawnType, float> lastSpawn;
    bool biasTriggered = false;
    int lastEnemy = 0;
    bool enemySpawned = false;
};