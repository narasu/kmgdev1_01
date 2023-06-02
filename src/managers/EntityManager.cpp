#include "Managers.h"


#include <algorithm>

EntityManager::EntityManager(std::unique_ptr<Player> _player) : player(std::move(_player)) {
    enemies = std::vector<std::unique_ptr<Enemy>>();
    background = std::vector<std::unique_ptr<Entity>>();
}

void EntityManager::updateAll(float _delta) {

    player->update(_delta);

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
            it = enemies.erase(it);
        }
        else {
            it++;
        }
    }

    checkCollisions();
}

void EntityManager::checkCollisions() {
    //if there are no enemies, no point in checking collisions
    if (enemies.empty()) {
        return;
    }
    
    //also, no point in checking collisions other than between enemy and player
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

std::vector<sf::Sprite> EntityManager::getSprites() {
    std::vector<sf::Sprite> sprites;
    for (const auto &it : background) {
        sprites.push_back(it->getSprite());
    }
    for (const auto &it : enemies) {
        sprites.push_back(it->getSprite());
    }
    sprites.push_back(player->getSprite());
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
    
    //background = std::make_unique<std::list<std::shared_ptr<Entity>>>(copyEntityList(*_entityManager.background));
}

EntityManager &EntityManager::operator=(const EntityManager &_entityManager) {
    if (this == &_entityManager) {
        return *this;
    }
    //background = std::make_unique<std::list<std::shared_ptr<Entity>>>(copyEntityList(*_entityManager.background));
    return *this;
}

Player &EntityManager::getPlayer() {
    return *player;
}
/*

std::list<std::shared_ptr<Entity>> EntityManager::copyEntityList(const std::list<std::shared_ptr<Entity>> &_list) {
    std::list<std::shared_ptr<Entity>> l;
    for (const auto & it : _list) {
        l.push_back(it);
    }
    return l;
}

*/
