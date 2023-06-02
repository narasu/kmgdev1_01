#include "Managers.h"

GameManager::GameManager() {
    state = "splash";
    stateEnter();
}

void GameManager::stateEnter() {
    if (state == "splash") {
        // show splash screen and start a timer or something idk
    }

    else if (state == "start") {
        // create entity manager, player, title, background, press key text
    }

    else if (state == "play") {
        // create spawner, health, score
    }

    else if (state == "lose") {
        // show "you died" text + score
    }

}

void GameManager::stateUpdate() {
    if (state == "splash") {
        // if timer runs out, go to start state
    }

    else if (state == "start") {
        // if key is pressed, go to play state
    }

    else if (state == "play") {
        // run update calls here? this might get messy
    }

    else if (state == "lose") {
        // if key is pressed or timer expired, go to start state
    }
}

void GameManager::stateExit() {
    if (state == "splash") {
        // remove splash screen
    }

    else if (state == "start") {
        // hide title, background, press key text
    }

    else if (state == "play") {
        // delete entitymanager and health
    }

    else if (state == "lose") {
        // delete "you died" text + score
    }
}

void GameManager::stateSwitch(std::string _state) {
    stateExit();
    state = _state;
    stateEnter();
}

std::string GameManager::getState() {
    return state;
}