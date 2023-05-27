#include "Spawner.h"

Spawner::Spawner() : xRange(320), spawnInterval(1.0f) {

}

Spawner::Spawner(int _xRange, float _spawnInterval) : xRange(_xRange), spawnInterval(_spawnInterval) {

}

bool Spawner::updateTimer(float _delta) {
    if (time < spawnInterval) {
        time += _delta;
        return false;
    }
    time = .0f;
    return true;
}

Enemy *Spawner::spawnEnemy(sf::Texture *_texture) {
    Enemy* enemy = new Enemy(_texture);
    float random = float(rand() % xRange);
    enemy->getSprite().setPosition(random, .0f);
    return enemy;
}