#include "Spawner.h"

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

Enemy *Spawner::spawnEnemy(sf::Texture *_texture, float _positionBias) {
    float randomPosition = float(rand() % viewportWidth);

    //move next spawn slightly away from the last one
    float offset = 30.0f;
    float p = lastSpawnPosition - randomPosition;
    while (fabsf(p) < offset) {
        int sign = (0 < p) - (p < 0);
        if (sign == 1) {
            randomPosition -= 1.0f;
        }
        else {
            randomPosition += 1.0f;
        }
        p = lastSpawnPosition - randomPosition;
    }

    //small chance that the enemy will spawn closer to the player, never twice in a row
    if (!biasTriggered) {
        int randomChance = rand() % 100;
        if (randomChance > 70) {
            float b = _positionBias - randomPosition;
            int sign = (0 < b) - (b < 0);
            std::cout << "moving to player" << std::endl;
            randomPosition += fabsf(_positionBias - randomPosition) * float(sign) * 0.75f;
            biasTriggered = true;
        }
    }
    biasTriggered = false;

    //lastly, keep spawns within the play area
    if (randomPosition < .0f) {
        randomPosition = .0f;
    }
    else if (randomPosition > 320.0f - offset) {
        randomPosition = 320.0f - offset;
    }

    lastSpawnPosition = randomPosition;
    return new Enemy(_texture, randomPosition, .0f);
}