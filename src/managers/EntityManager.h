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
    std::unique_ptr<std::list<std::shared_ptr<Entity>>>& getEntityList();
    void addEntity(const std::shared_ptr<Entity> &_entity);
private:
    std::unique_ptr<std::list<std::shared_ptr<Entity>>> entityList;
    std::list<std::shared_ptr<Entity>> copyEntityList(const std::list<std::shared_ptr<Entity>> &_list);
};
