#include "Managers.h"
#include "../enums/StateType.h"

#pragma once

class GameManager {
public:
    GameManager(std::shared_ptr<TextureManager> _textureManager,
                std::shared_ptr<EntityManager> _entityManager,
                std::shared_ptr<InterfaceManager> _interfaceManager);
    GameManager(const GameManager&  _gameManager); //copy constructor
    GameManager& operator=(const GameManager& _gameManager); //assignment operator
    void stateUpdate();
    void switchState(StateType _state);
    int getStage() { return stage; }
private:
    void stateEnter();
    void stateExit();
    StateType state;
    sf::Clock deltaClock;
    float timer = .0f;
    int score = 0;
    int stage = 0;

    std::unique_ptr<Spawner> spawner;
    std::unique_ptr<AudioManager> audioManager;
    std::shared_ptr<TextureManager> textureManager;
    std::shared_ptr<EntityManager> entityManager;
    std::shared_ptr<InterfaceManager> interfaceManager;
};