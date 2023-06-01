#include "Managers.h"


EntityManager::EntityManager() : entityList(std::make_unique<std::list<std::shared_ptr<Entity>>>()) {
}

void EntityManager::updateAll(float _delta, float _boundsY) {
    for(auto it = entityList->begin(); it!=entityList->end();) {
        (*it)->update(_delta);

        //if an entity reaches the bottom of the screen, delete it
        if ((*it)->getSprite().getPosition().y > _boundsY) {
            //it->reset();
            it = entityList->erase(it);
        }
        else {
            it++;
        }
    }
}

void EntityManager::addEntity(const std::shared_ptr<Entity> &_entity) {
    entityList->push_back(_entity);
}


std::unique_ptr<std::list<std::shared_ptr<Entity>>>& EntityManager::getEntityList() {
    return entityList;
}


EntityManager::~EntityManager() {

    entityList->clear();
}

EntityManager::EntityManager(const EntityManager &_entityManager) {
    if (this == &_entityManager) {
        return;
    }
    entityList = std::make_unique<std::list<std::shared_ptr<Entity>>>(copyEntityList(*_entityManager.entityList));
}

EntityManager &EntityManager::operator=(const EntityManager &_entityManager) {
    if (this == &_entityManager) {
        return *this;
    }
    entityList = std::make_unique<std::list<std::shared_ptr<Entity>>>(copyEntityList(*_entityManager.entityList));
    return *this;
}

std::list<std::shared_ptr<Entity>> EntityManager::copyEntityList(const std::list<std::shared_ptr<Entity>> &_list) {
    std::list<std::shared_ptr<Entity>> l;
    for (const auto & it : _list) {
        l.push_back(it);
    }
    return l;
}