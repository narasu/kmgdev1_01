#include "Managers.h"
#pragma once

class GameManager {
public:
    explicit GameManager(std::shared_ptr<EntityManager> _entityManager, std::shared_ptr<TextureManager> _textureManager);

    void stateUpdate(float _delta);
    void stateSwitch(std::string _state);
    std::string getState();

private:
    void stateEnter();
    void stateExit();
    std::string state;

    std::shared_ptr<EntityManager> entityManager;
    std::shared_ptr<TextureManager> textureManager;
};