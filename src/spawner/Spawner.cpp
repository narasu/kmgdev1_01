#include "Spawner.h"
#include "../GameData.h"

Spawner::Spawner(float _enemySpawnInterval, float _grassSpawnInterval) {
    spawnIntervals[SpawnType::ENEMY] = _enemySpawnInterval;
    spawnIntervals[SpawnType::GRASS] = _grassSpawnInterval;
}

void Spawner::updateTimer(SpawnType _type, float _delta) {
    time[_type] += _delta;
}

bool Spawner::intervalReached(SpawnType _type, float _delta) {

    if (time[_type] < spawnIntervals[_type]) {
        return false;
    }
    time [_type] = .0f;
    return true;
}

std::unique_ptr<Enemy> Spawner::spawnEnemy(const sf::Texture &_texture, Rect<float> _bounds, float _yForce, float _playerX) {
    auto randomPosition = generateRandomPosition(lastSpawn[SpawnType::ENEMY], 20.0f);

    // chance that the enemy will spawn closer to the player, never twice in a row
    if (!biasTriggered) {
        int randomChance = rand() % 100;
        if (randomChance > 40) {
            float b = _playerX - randomPosition;
            randomPosition += fabsf(_playerX - randomPosition) * Mathf::signf(b) * 0.85f;
            biasTriggered = true;
        }
    }
    else {
        biasTriggered = false;
    }
    return std::make_unique<Enemy>(_texture, randomPosition, HUD_HEIGHT, _bounds, _yForce);
}

std::unique_ptr<Grass> Spawner::spawnGrass(const sf::Texture &_texture, float _speedY) {
    auto randomPosition = generateRandomPosition(lastSpawn[SpawnType::GRASS], 60.0f);
    return std::make_unique<Grass>(_texture, randomPosition, HUD_HEIGHT, _speedY);
}

void Spawner::setSpawnInterval(SpawnType _type, float _seconds) {
    spawnIntervals[_type] = _seconds;
}

float Spawner::generateRandomPosition(float &_last, float _offset) {
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

    auto randomChance = rand() % 100;
    if (randomChance > 50) {
        randomPosition += static_cast<float>((rand() % 60) * -Mathf::sign(p));
    }

    // keep spawns within the play area, on the opposite side to avoid negating previous offset
    auto vpWidthf = static_cast<float>(VIEWPORT_WIDTH);
    if (randomPosition < 5.0f) {
        randomPosition += vpWidthf - 10.0f;
    }
    else if (randomPosition > vpWidthf - 5.0f) {
        randomPosition -= vpWidthf - 10.0f;
    }
    _last = randomPosition;
}
