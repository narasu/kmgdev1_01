//This class manages pointers to each instance of Entity and runs all their update calls.
#include <list>
#include "Managers.h"
#include "../entity/Entity.h"
#pragma once

class EntityManager {
public:
    EntityManager();
    ~EntityManager();
    EntityManager(const EntityManager&  _entityManager); //copy constructor
    EntityManager& operator=(const EntityManager& _entityManager); //assignment operator
    void updateAll(float _delta, float _boundsY);
    std::list<Entity*> getEntityList();
    void addEntity(Entity* _entity);
private:
    std::list<Entity*> *entityList;
    std::list<Entity*> copyEntityList(std::list<Entity *> &_list);
};
