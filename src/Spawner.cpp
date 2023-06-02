#include "Spawner.h"
#include "GameData.h"

Spawner::Spawner() : spawnInterval(1.0f) {}

Spawner::Spawner(float _spawnInterval) : spawnInterval(_spawnInterval) {}

bool Spawner::updateTimer(float _delta) {
    if (time < spawnInterval) {
        time += _delta;
        return false;
    }
    time = .0f;
    return true;
}

std::unique_ptr<Enemy> Spawner::spawnEnemy(const sf::Texture &_texture, const Rect<float> _bounds, float _playerX) {
    auto randomPosition = static_cast<float>(rand() % VIEWPORT_WIDTH);

    //move next spawn slightly away from the last one
    float offset = 20.0f;
    float p = lastSpawnPosition - randomPosition;
    while (fabsf(p) < offset) {
        if (Mathf::sign(p) == 1) {
            randomPosition -= 1.0f;
        }
        else {
            randomPosition += 1.0f;
        }
        p = lastSpawnPosition - randomPosition;
    }

    //keep spawns within the play area, on the opposite side to avoid negating previous offset
    auto vpWidthf = static_cast<float>(VIEWPORT_WIDTH);
    if (randomPosition < .0f) {
        randomPosition += vpWidthf;
    }
    else if (randomPosition > vpWidthf - offset) {
        randomPosition -= vpWidthf - offset;
    }

    //small chance that the enemy will spawn closer to the player, never twice in a row
    if (!biasTriggered) {
        int randomChance = rand() % 100;
        if (randomChance > 70) {
            float b = _playerX - randomPosition;
            randomPosition += fabsf(_playerX - randomPosition) * Mathf::signf(b) * 0.85f;
            biasTriggered = true;
        }
    }
    else {
        biasTriggered = false;
    }

    lastSpawnPosition = randomPosition;
    return std::make_unique<Enemy>(_texture, randomPosition, .0f, _bounds);
}