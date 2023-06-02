#include "Managers.h"
#pragma once

class GameManager {
public:
    GameManager();

    void stateUpdate(float _delta);
    void stateSwitch(std::string _state);
    std::string getState();
    EntityManager &getEntityManager();
private:
    void stateEnter();
    void stateExit();
    std::string state;

    std::unique_ptr<EntityManager> entityManager;
};