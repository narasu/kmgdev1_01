#include <SFML/Graphics.hpp>
#include "Enemy.h"
#pragma once

class Spawner {
public:
    Spawner();
    Spawner(int _viewportWidth, float _spawnInterval);
    bool updateTimer(float _delta);
    Enemy *spawnEnemy(sf::Texture* _texture);
private:
    int viewportWidth;
    float spawnInterval;
    float time = .0f;

};