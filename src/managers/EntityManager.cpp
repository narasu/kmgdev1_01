#include "Managers.h"

#include <algorithm>

EntityManager::EntityManager(std::shared_ptr<Player> &_player) : player(_player){
    enemies = std::make_unique<std::vector<std::shared_ptr<Enemy>>>();
    background = std::make_unique<std::vector<std::shared_ptr<Entity>>>();
    hud = std::make_unique<std::vector<std::shared_ptr<Entity>>>();
}

void EntityManager::updateAll(float _delta, float _boundsY) {

    player->update(_delta);
    for(auto it = enemies->begin(); it != enemies->end();) {
        (*it)->update(_delta);
        //if an enemy reaches the bottom of the screen, erase it from the list
        if ((*it)->getSprite().getPosition().y > _boundsY) {
            it = enemies->erase(it);
        }
        else {
            it++;
        }
    }

    checkCollisions();
}

void EntityManager::checkCollisions() {
    //if there are no enemies, no point in checking collisions
    if (enemies->empty()) {
        return;
    }
    for (const auto& e : *enemies) {
        if (Rect<float>::isOverlapping(e->getBoundsGlobal(), player->getBoundsGlobal())) {
            e->onCollision();
            player->onCollision();
        }
    }
}

void EntityManager::addEnemy(const std::shared_ptr<Enemy> &_enemy) {
    enemies->push_back(_enemy);
}


std::vector<std::shared_ptr<Entity>> EntityManager::getEntityList() {
    std::vector<std::shared_ptr<Entity>> l;
    for (const auto &it : *background) {
        l.push_back(it);
    }
    for (const auto &it : *enemies) {
        l.push_back(it);
    }
    l.push_back(player);
    for (const auto &it : *hud) {
        l.push_back(it);
    }
    return l;
}


EntityManager::~EntityManager() {

    background->clear();
    enemies->clear();
}

EntityManager::EntityManager(const EntityManager &_entityManager) : player(_entityManager.player) {
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
/*

std::list<std::shared_ptr<Entity>> EntityManager::copyEntityList(const std::list<std::shared_ptr<Entity>> &_list) {
    std::list<std::shared_ptr<Entity>> l;
    for (const auto & it : _list) {
        l.push_back(it);
    }
    return l;
}

*/
