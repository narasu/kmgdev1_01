//This class manages pointers to each instance of Entity and runs all their update calls.
#include <list>
#include "Managers.h"
#include "../entity/Entity.h"
#include "../Player.h"
#include "../Enemy.h"
#pragma once

class EntityManager {
public:
    EntityManager(std::shared_ptr<Player> &_player);
    ~EntityManager();
    EntityManager(const EntityManager&  _entityManager); //copy constructor
    EntityManager& operator=(const EntityManager& _entityManager); //assignment operator
    void updateAll(float _delta, float _boundsY);
    std::vector<std::shared_ptr<Entity>> getEntityList();
    void addEnemy(const std::shared_ptr<Enemy> &_enemy);
    void addBackground(const std::shared_ptr<Entity> &_entity);
    void checkCollisions();
private:
    std::shared_ptr<Player> &player;
    std::unique_ptr<std::vector<std::shared_ptr<Enemy>>> enemies;
    std::unique_ptr<std::vector<std::shared_ptr<Entity>>> background;
    std::unique_ptr<std::vector<std::shared_ptr<Entity>>> hud;
    //std::list<std::shared_ptr<Entity>> copyEntityList(const std::list<std::shared_ptr<Entity>> &_list);

};
