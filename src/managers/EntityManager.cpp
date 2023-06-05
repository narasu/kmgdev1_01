#include "Managers.h"
#include <algorithm>

//TODO: Re-implement assignment operator and copy constructor

EntityManager::EntityManager() {
    enemies = std::vector<std::unique_ptr<Enemy>>();
    grass = std::vector<std::unique_ptr<Grass>>();
}

EntityManager::EntityManager(std::unique_ptr<Player> _player) : EntityManager() {
    player = std::move(_player);
}

EntityManager::~EntityManager() {
    clearAll();
}

EntityManager::EntityManager(const EntityManager &_entityManager) {
    if (this == &_entityManager) {
        return;
    }

    //background = std::make_unique<std::list<std::shared_ptr<BaseEntity>>>(copyEntityList(*_entityManager.background));
}

EntityManager &EntityManager::operator=(const EntityManager &_entityManager) {
    if (this == &_entityManager) {
        return *this;
    }
    //background = std::make_unique<std::list<std::shared_ptr<BaseEntity>>>(copyEntityList(*_entityManager.background));
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

void EntityManager::setPlayer(std::unique_ptr<Player> _player) {
    player = std::move(_player);
}

void EntityManager::addEnemy(std::unique_ptr<Enemy> _enemy) {
    enemies.emplace_back(std::move(_enemy));
}

void EntityManager::addGrass(std::unique_ptr<Grass> _grass) {
    grass.emplace_back(std::move(_grass));
}

Player &EntityManager::getPlayer() {
    return *player;
}

const std::vector<std::unique_ptr<Enemy>>& EntityManager::getEnemies() {
    return enemies;
}

const std::vector<std::unique_ptr<Grass>>& EntityManager::getGrass() {
    return grass;
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

int EntityManager::getEnemyOutOfBoundsCount() {
    return enemyOutOfBoundsCount;
}

void EntityManager::clearAll() {
    player.reset();
    grass.clear();
    enemies.clear();
}




/*

std::list<std::shared_ptr<BaseEntity>> EntityManager::copyEntityList(const std::list<std::shared_ptr<BaseEntity>> &_list) {
    std::list<std::shared_ptr<BaseEntity>> l;
    for (const auto & it : _list) {
        l.push_back(it);
    }
    return l;
}

*/
