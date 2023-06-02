#include "Managers.h"
#pragma once

class GameManager {
public:
    GameManager();

    void stateUpdate();
    void stateSwitch(std::string _state);
    std::string getState();
private:
    std::string state;
    void stateEnter();
    void stateExit();
};