#include "Managers.h"
#include <algorithm>

EntityManager::EntityManager(std::unique_ptr<Player> _player) {
    player = std::move(_player);
}

EntityManager::~EntityManager() {
    clearAll();
}

EntityManager::EntityManager(const EntityManager &_entityManager) {
    if (this == &_entityManager) {
        return;
    }
    player = std::make_unique<Player>(*_entityManager.player);
    for (auto & it : _entityManager.enemies) {
        enemies.push_back(std::make_unique<Enemy>(*it));
    }
    for (auto & it : _entityManager.grass) {
        grass.push_back(std::make_unique<Grass>(*it));
    }
}

EntityManager &EntityManager::operator=(const EntityManager &_entityManager) {
    if (this == &_entityManager) {
        return *this;
    }
    clearAll(); //not sure if necessary
    player = std::make_unique<Player>(*_entityManager.player);
    for (auto & it : _entityManager.enemies) {
        enemies.push_back(std::make_unique<Enemy>(*it));
    }
    for (auto & it : _entityManager.grass) {
        grass.push_back(std::make_unique<Grass>(*it));
    }
    return *this;
}

void EntityManager::updateAll(float _delta) {
    enemyOutOfBoundsCount = 0;
    if (player!=nullptr) {
        player->update(_delta);
    }

    for(auto it = grass.begin(); it != grass.end();) {
        (*it)->update(_delta);

        if ((*it)->isDestroyed()) {
            it = grass.erase(it);
        }
        else {
            it++;
        }
    }

    for(auto it = enemies.begin(); it != enemies.end();) {
        (*it)->update(_delta);
        if ((*it)->isDestroyed()) {
            if ((*it)->isOutOfBounds()) {
                enemyOutOfBoundsCount+=1;
            }
            it = enemies.erase(it);
        }
        else {
            it++;
        }
    }

    checkCollisions();
}

void EntityManager::checkCollisions() {
    if (enemies.empty() || player==nullptr) {
        return;
    }

    for (const auto& e : enemies) {
        if (Rect<float>::isOverlapping(e->getBoundsGlobal(), player->getBoundsGlobal())) {
            e->onCollision();
            player->onCollision();
        }
    }
}

void EntityManager::clearAll() {
    player.reset();
    grass.clear();
    enemies.clear();
}

std::vector<std::reference_wrapper<sf::Sprite>> EntityManager::getSprites() {
    std::vector<std::reference_wrapper<sf::Sprite>> s;
    for (auto & it : grass) {
        s.emplace_back(it->getSprite());
    }
    for (auto & it : enemies) {
        s.emplace_back(it->getSprite());
    }
    if (player != nullptr) {
        s.emplace_back(player->getSprite());
    }
    return s;
}
