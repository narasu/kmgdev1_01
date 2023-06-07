#include "../managers/Managers.h"


Spawner::Spawner(std::shared_ptr<TextureManager> _textureManager, std::shared_ptr<EntityManager> _entityManager) :
textureManager(_textureManager), entityManager(_entityManager) {
    spawnIntervals[ENEMY] = ENEMY_SPAWN_INTERVAL[0];
    spawnIntervals[GRASS] = GRASS_SPAWN_INTERVAL[0];
}

void Spawner::update(int _stage, float _delta, float _playerX) {
    if (timerActive[ENEMY] && _playerX >= -1.0f) {
        time[ENEMY] += _delta;
        if (intervalReached(ENEMY)) {
            spawnEnemy(_stage, 1, _playerX);
        }
    }
    if (timerActive[GRASS]) {
        time[GRASS] += _delta;
        if (intervalReached(GRASS)) {
            spawnGrass(_stage, rand() % 2 + 1);
        }
    }
}

bool Spawner::intervalReached(SpawnType _type) {
    if (time[_type] >= spawnIntervals[_type]) {
        time[_type] = .0f;
        return true;
    }
    return false;
}

void Spawner::spawnEnemy(int _stage, int _count, float _playerX) {
    while (_count > 0) {
        auto randomPosition = generateRandomPosition(lastSpawn[ENEMY], 15.0f);

        // chance that the enemy will spawn directly above the player, never twice in a row
        if (!biasTriggered) {
            int randomChance = rand() % 100;
            if (randomChance > 40) {
                float b = _playerX - randomPosition;
                //randomPosition += fabsf(_playerX - randomPosition) * Mathf::signf(b) * 0.85f;
                randomPosition = _playerX;
                biasTriggered = true;
            }
        }
        else {
            biasTriggered = false;
        }


        // get random texture, never the same twice
        int random123 = rand() % 3 + 1;
        if (lastEnemy != 0) {
            while (random123 == lastEnemy) {
                random123 = rand() % 3 + 1;
            }
        }

        lastEnemy = random123;
        std::string randomEnemy = "enemy0" + std::to_string(random123);
        std::cout << randomEnemy <<std::endl;
        entityManager->addEnemy(
                std::make_unique<Enemy>(
                        *textureManager->getTexture(randomEnemy),
                        randomPosition,
                        static_cast<float>(HUD_HEIGHT),
                        BOUNDS.at(randomEnemy),
                        ENEMY_FORCE_Y[_stage])
        );
        _count--;
    }
    enemySpawned = true;
}

void Spawner::spawnGrass(int _stage, int _count) {

    while (_count > 0) {
        auto randomPosition = generateRandomPosition(lastSpawn[GRASS], 25.0f);
        entityManager->addGrass(
                std::make_unique<Grass>(
                        *textureManager->getTexture("grass"),
                        randomPosition,
                        static_cast<float>(HUD_HEIGHT),
                        STAGE_SPEED[_stage])
        );
        _count--;
    }
}

float Spawner::generateRandomPosition(float _last, float _offset) {
    auto randomPosition = static_cast<float>(rand() % VIEWPORT_WIDTH);
    // move next spawn away from the last one
    float p = _last - randomPosition;
    while (fabsf(p) < _offset) {
        if (Mathf::sign(p) == 1) {
            randomPosition -= 1.0f;
        }
        else {
            randomPosition += 1.0f;
        }
        p = _last - randomPosition;
    }

    // keep spawns within the play area, on the opposite side to avoid negating previous offset
    auto vpWidthf = static_cast<float>(VIEWPORT_WIDTH);
    if (randomPosition < 2.0f) {
        randomPosition += vpWidthf - 4.0f;
    }
    else if (randomPosition > vpWidthf - 2.0f) {
        randomPosition -= vpWidthf - 4.0f;
    }

    return randomPosition;
}


void Spawner::setTimerActive(SpawnType _type, bool _active) {
    if (timerActive[_type] != _active) {
        timerActive[_type] = _active;

        if (_type == ENEMY) {
            time[_type] = .0f;
        }
    }
}

Spawner::Spawner(const Spawner &_spawner) {
    if (this == &_spawner) {
        return;
    }
    textureManager = _spawner.textureManager;
    entityManager = _spawner.entityManager;
    time = _spawner.time;
    timerActive = _spawner.timerActive;
    spawnIntervals = _spawner.spawnIntervals;
    lastSpawn = _spawner.lastSpawn;
}

Spawner &Spawner::operator=(const Spawner &_spawner) {
    if (this == &_spawner) {
        return *this;
    }
    textureManager = _spawner.textureManager;
    entityManager = _spawner.entityManager;
    time = _spawner.time;
    timerActive = _spawner.timerActive;
    spawnIntervals = _spawner.spawnIntervals;
    lastSpawn = _spawner.lastSpawn;
    return *this;
}


