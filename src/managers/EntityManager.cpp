#include "Managers.h"

#include <algorithm>

//TODO: Re-implement assignment operator and copy constructor

EntityManager::EntityManager() {
    enemies = std::vector<std::unique_ptr<Enemy>>();
    background = std::vector<std::unique_ptr<BaseEntity>>();
}

EntityManager::EntityManager(std::unique_ptr<Player> _player) : EntityManager() {
    player = std::move(_player);
}

void EntityManager::updateAll(float _delta) {
    outOfBoundsCount = 0;
    if (player!=nullptr) {
        player->update(_delta);
    }

    for(auto it = background.begin(); it != background.end();) {
        (*it)->update(_delta);

        if ((*it)->isDestroyed()) {
            it = background.erase(it);
        }
        else {
            it++;
        }
    }

    for(auto it = enemies.begin(); it != enemies.end();) {
        (*it)->update(_delta);

        if ((*it)->isDestroyed()) {
            if ((*it)->isOutOfBounds()) {
                outOfBoundsCount++;
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

void EntityManager::addEnemy(std::unique_ptr<Enemy> _enemy) {
    enemies.push_back(std::move(_enemy));
}

std::vector<std::reference_wrapper<sf::Sprite>> EntityManager::getSprites() {
    std::vector<std::reference_wrapper<sf::Sprite>> sprites;
    for (const auto &it : background) {
        sprites.emplace_back(it->getSprite());
    }
    for (const auto &it : enemies) {
        sprites.emplace_back(it->getSprite());
    }
    if (player!=nullptr) {
        sprites.emplace_back(player->getSprite());
    }
    return sprites;
}


EntityManager::~EntityManager() {
    background.clear();
    enemies.clear();
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

Player &EntityManager::getPlayer() {
    return *player;
}

void EntityManager::setPlayer(std::unique_ptr<Player> _player) {
    player = std::move(_player);
}

void EntityManager::clearAll() {
    player.reset();
    background.clear();
    enemies.clear();
}

int EntityManager::getOutOfBoundsCount() {
    return outOfBoundsCount;
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
