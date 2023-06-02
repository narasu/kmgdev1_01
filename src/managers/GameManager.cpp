#include "Managers.h"
#include "../GameData.h"

GameManager::GameManager(std::shared_ptr<EntityManager> _entityManager, std::shared_ptr<TextureManager> _textureManager) :
entityManager(_entityManager), textureManager(_textureManager){

    state = "start";
    stateEnter();
}

void GameManager::stateEnter() {
    if (state == "splash") {
        // show splash screen and start a timer or something idk
    }

    else if (state == "start") {
        // create player, title, background, press key text
        entityManager->setPlayer(
                std::make_unique<Player>(*textureManager->getTexture("player"), BOUNDS.at("player"))
                );
    }

    else if (state == "play") {
        // create spawner, health, score
    }

    else if (state == "lose") {
        // show "you died" text + score
    }

}

void GameManager::stateUpdate(float _delta) {
    if (state == "splash") {
        // if timer runs out, go to start state
    }

    else if (state == "start") {
        // if key is pressed, go to play state
    }

    else if (state == "play") {
        // run update calls here? this might get messy

        // and what about draw calls?
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
