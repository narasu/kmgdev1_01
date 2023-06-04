#include "Managers.h"
#include "../GameData.h"

//TODO: implement copy constructor and assignment operator

GameManager::GameManager(std::shared_ptr<EntityManager> _entityManager, std::shared_ptr<InterfaceManager> _interfaceManager) :
entityManager(_entityManager), interfaceManager(_interfaceManager) {
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
                std::make_unique<Player>(*textureManager.getTexture("player"), BOUNDS.at("player"))
                );
    }

    else if (state == "play") {
        std::cout << "play state entered" << std::endl;
        // create spawner, health, score
        spawner = std::make_unique<Spawner>(SPAWN_INTERVAL[0]);
    }

    else if (state == "lose") {
        // show "you died" text + score
    }

}

void GameManager::stateUpdate() {
    auto deltaTime = deltaClock.restart();

    if (state == "splash") {
        // if timer runs out, go to start state
    }

    else if (state == "start") {
        entityManager->updateAll(deltaTime.asSeconds());

        // go to play state when the player moves
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            switchState("play");
            return;
        }
    }

    else if (state == "play") {
        if (entityManager->getPlayer().isDestroyed()) {
            switchState("lose");
            return;
        }

        // spawn a random enemy every few seconds
        if (spawner->updateTimer(deltaTime.asSeconds())) {
            int random123 = rand() % 3 + 1;
            std::string randomEnemy = "enemy0" + std::to_string(random123);
            entityManager->addEnemy(
                    spawner->spawnEnemy(
                            *textureManager.getTexture(randomEnemy),
                            BOUNDS.at(randomEnemy),
                            entityManager->getPlayer().getPosition().x)
            );
        }

        entityManager->updateAll(deltaTime.asSeconds());
        // draw calls here maybe?
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
        // delete all entities and health
        entityManager->removeAll();
    }

    else if (state == "lose") {
        // delete "you died" text + score
    }
}

void GameManager::switchState(std::string _state) {
    stateExit();
    state = _state;
    stateEnter();
}

std::string GameManager::getState() {
    return state;
}
