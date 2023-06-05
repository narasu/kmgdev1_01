//This class manages pointers to the player, enemies and background objects, and runs all their update calls.
#include <list>
#include "Managers.h"
#include "../entity/BaseEntity.h"
#include "../entity/Player.h"
#include "../entity/Enemy.h"
#include "../entity/Grass.h"

#pragma once

class EntityManager {
public:
    EntityManager();
    explicit EntityManager(std::unique_ptr<Player> _player);
    ~EntityManager();
    EntityManager(const EntityManager&  _entityManager); //copy constructor
    EntityManager& operator=(const EntityManager& _entityManager); //assignment operator
    void updateAll(float _delta);
    void setPlayer(std::unique_ptr<Player> _player);
    void addEnemy(std::unique_ptr<Enemy> _enemy);
    void addGrass(std::unique_ptr<Grass> _grass);
    void clearAll();
    Player &getPlayer();
    const std::vector<std::unique_ptr<Enemy>>& getEnemies();
    const std::vector<std::unique_ptr<Grass>>& getGrass();
    std::vector<std::reference_wrapper<sf::Sprite>> getSprites();
    int getEnemyOutOfBoundsCount();
private:
    void checkCollisions();
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Grass>> grass;
    int enemyOutOfBoundsCount;
    //std::list<std::shared_ptr<BaseEntity>> copyEntityList(const std::list<std::shared_ptr<BaseEntity>> &_list);

};
