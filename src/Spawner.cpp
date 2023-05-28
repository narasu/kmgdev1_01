#include "Spawner.h"

Spawner::Spawner() : viewportWidth(320), spawnInterval(1.0f) {

}

Spawner::Spawner(int _viewportWidth, float _spawnInterval) : viewportWidth(_viewportWidth), spawnInterval(_spawnInterval) {

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

    float random = float(rand() % (viewportWidth - 20)) + 10.0f;
    Enemy* enemy = new Enemy(_texture, random, .0f);
    enemy->getSprite().setPosition(random, .0f);
    return enemy;
}