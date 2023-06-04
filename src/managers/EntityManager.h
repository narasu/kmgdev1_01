//This class manages pointers to the player, enemies and background objects, and runs all their update calls.
#include <list>
#include "Managers.h"
#include "../entity/Entity.h"
#include "../Player.h"
#include "../Enemy.h"
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
    void addBackground(std::unique_ptr<Entity> _entity);
    void addInterface(std::unique_ptr<Entity> _entity);
    void removeAll();
    std::vector<std::reference_wrapper<sf::Sprite>> getSprites();
    Player &getPlayer();
    int getOutOfBoundsCount();
private:
    void checkCollisions();
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Entity>> background;
    std::vector<std::unique_ptr<Entity>> interface;
    int outOfBoundsCount;
    //std::list<std::shared_ptr<Entity>> copyEntityList(const std::list<std::shared_ptr<Entity>> &_list);

};
