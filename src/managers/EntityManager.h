//This class manages pointers to the player, enemies and background objects, and runs all their update calls.
#include <list>
#include "Managers.h"
#include "../entity/Player.h"
#include "../entity/Enemy.h"
#include "../entity/Grass.h"

#pragma once

class EntityManager {
public:
    EntityManager() = default;
    explicit EntityManager(std::unique_ptr<Player> _player);
    ~EntityManager();
    EntityManager(const EntityManager&  _entityManager); //copy constructor
    EntityManager& operator=(const EntityManager& _entityManager); //assignment operator
    void updateAll(float _delta);
    void clearAll();
    std::vector<std::reference_wrapper<sf::Sprite>> getSprites();
    Player &getPlayer() { return *player; }
    void setPlayer(std::unique_ptr<Player> _player) { player = std::move(_player); }
    void addEnemy(std::unique_ptr<Enemy> _enemy) { enemies.emplace_back(std::move(_enemy)); }
    void addGrass(std::unique_ptr<Grass> _grass) { grass.emplace_back(std::move(_grass)); }
    const std::vector<std::unique_ptr<Enemy>>& getEnemies() { return enemies; }
    const std::vector<std::unique_ptr<Grass>>& getGrass() { return grass; }
    int getEnemyOutOfBoundsCount() { return enemyOutOfBoundsCount; }
private:
    void checkCollisions();
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Grass>> grass;
    int enemyOutOfBoundsCount = 0;
    //std::list<std::shared_ptr<BaseEntity>> copyEntityList(const std::list<std::shared_ptr<BaseEntity>> &_list);

};
