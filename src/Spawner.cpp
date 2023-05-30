#include "Spawner.h"
#include "hiro/Mathf.h"

Spawner::Spawner() : viewportWidth(320), spawnInterval(1.0f) {}

Spawner::Spawner(int _viewportWidth, float _spawnInterval) : viewportWidth(_viewportWidth), spawnInterval(_spawnInterval) {}

bool Spawner::updateTimer(float _delta) {
    if (time < spawnInterval) {
        time += _delta;
        return false;
    }
    time = .0f;
    return true;
}

Enemy *Spawner::spawnEnemy(sf::Texture *_texture, float _playerX) {
    float randomPosition = static_cast<float>(rand() % viewportWidth);

    //move next spawn slightly away from the last one
    float offset = 20.0f;
    float p = lastSpawnPosition - randomPosition;
    while (fabsf(p) < offset) {

        int sign = Hiro::Mathf::sign(p);
        if (sign == 1) {
            randomPosition -= 1.0f;
        }
        else {
            randomPosition += 1.0f;
        }
        p = lastSpawnPosition - randomPosition;
    }

    //keep spawns within the play area, on the opposite side to avoid negating previous offset
    float vpWidthf = static_cast<float>(viewportWidth);
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
            int sign = Hiro::Mathf::sign(b);
            randomPosition += fabsf(_playerX - randomPosition) * static_cast<float>(sign) * 0.85f;
            biasTriggered = true;
        }
    }
    biasTriggered = false;

    lastSpawnPosition = randomPosition;
    return new Enemy(_texture, randomPosition, .0f);
}