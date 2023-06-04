#include "Managers.h"
#include "../Spawner.h"
#pragma once

class GameManager {
public:
    GameManager(std::shared_ptr<TextureManager> _textureManager, std::shared_ptr<EntityManager> _entityManager, std::shared_ptr<InterfaceManager> _interfaceManager);

    void stateUpdate();
    void switchState(std::string _state);
    std::string getState();

private:
    void stateEnter();
    void stateExit();
    std::string state;
    sf::Clock deltaClock;
    float timer = .0f;
    int score = 0;
    int stage = 0;

    std::unique_ptr<Spawner> spawner;
    std::shared_ptr<TextureManager> textureManager;
    std::shared_ptr<EntityManager> entityManager;
    std::shared_ptr<InterfaceManager> interfaceManager;
};