#include "EntityManager.h"

EntityManager::EntityManager() : entityList(new std::list<Entity*>) {
}

void EntityManager::updateAll(float _delta, float _boundsY) {
    for(std::list<Entity*>::iterator it = entityList->begin(); it!=entityList->end();) {
        (*it)->update(_delta);


        //if an entity reaches the bottom of the screen, delete it
        if ((*it)->getSprite().getPosition().y > _boundsY) {
            delete *it;
            it = entityList->erase(it);
        }
        else {
            it++;
        }
    }
}

void EntityManager::addEntity(Entity *_entity) {
    entityList->push_back(_entity);
}


std::list<Entity *> EntityManager::getEntityList() {
    return *entityList;
}


EntityManager::~EntityManager() {
    for (std::list<Entity*>::const_iterator it = entityList->begin(); it != entityList->end(); ++it) {
        delete *it;
    }
    entityList->clear();
    delete entityList;
    entityList = nullptr;
}

EntityManager::EntityManager(const EntityManager &_entityManager) {
    if (this == &_entityManager) {
        return;
    }
    entityList = new std::list<Entity*>(copyEntityList(*_entityManager.entityList));
}

EntityManager &EntityManager::operator=(const EntityManager &_entityManager) {
    if (this == &_entityManager) {
        return *this;
    }
    entityList = new std::list<Entity*>(copyEntityList(*_entityManager.entityList));
    return *this;
}

std::list<Entity *> EntityManager::copyEntityList(std::list<Entity *> &_list) {
    std::list<Entity *> l;
    for (std::list<Entity*>::const_iterator it = _list.begin(); it != _list.end(); ++it) {
        l.push_back(*it);
    }
    return l;
}
