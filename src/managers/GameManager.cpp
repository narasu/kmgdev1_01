// Executive class that handles game states with a basic finite state machine
//

#include "Managers.h"
#include "../GameData.h"

//TODO: implement copy constructor and assignment operator

GameManager::GameManager(std::shared_ptr<TextureManager> _textureManager, std::shared_ptr<EntityManager> _entityManager, std::shared_ptr<InterfaceManager> _interfaceManager) :
textureManager(_textureManager), entityManager(_entityManager), interfaceManager(_interfaceManager) {
    state = "splash";
    stateEnter();
}

void GameManager::stateEnter() {
    if (state == "splash") {
        interfaceManager->displayImage("splash", Vector2<float>(VIEWPORT_WIDTH*0.5f, VIEWPORT_HEIGHT*0.5f));
    }

    else if (state == "start") {
        spawner = std::make_unique<Spawner>(SPAWN_INTERVAL[0]);
        entityManager->setPlayer(
                std::make_unique<Player>(*textureManager->getTexture("player"), BOUNDS.at("player"))
                );
        interfaceManager->displayImage("title", Vector2<float>(VIEWPORT_WIDTH * 0.5f, 35.0f));
        interfaceManager->displayImage("start_text", Vector2<float>(VIEWPORT_WIDTH * 0.5f, VIEWPORT_HEIGHT * 0.5f + 20.0f));
    }

    else if (state == "play") {

        auto offset = Vector2<int>(6,3);
        interfaceManager->displayImage("score", Vector2<float>(offset.x, offset.y), false);
        interfaceManager->initializeScoreAndHealth(offset);
    }

    else if (state == "lose") {
        interfaceManager->displayImage("end_text", Vector2<float>(VIEWPORT_WIDTH * 0.5f, VIEWPORT_HEIGHT * 0.5f - 12.0f));
        interfaceManager->displayImage("score", Vector2<float>(VIEWPORT_WIDTH * 0.5f - 50.0f, VIEWPORT_HEIGHT * 0.5f), false);
        interfaceManager->showFinalScore();
    }
}

void GameManager::stateUpdate() {
    auto deltaTime = deltaClock.restart();

    if (state == "splash") {
        timer += deltaTime.asSeconds();
        if (timer >= 3.0f) {
            switchState("start");
            timer = .0f;
            return;
        }
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
        if (spawner->intervalReached(deltaTime.asSeconds())) {
            int random123 = rand() % 3 + 1;
            std::string randomEnemy = "enemy0" + std::to_string(random123);
            entityManager->addEnemy(
                    spawner->spawnEnemy(
                            *textureManager->getTexture(randomEnemy),
                            BOUNDS.at(randomEnemy),
                            entityManager->getPlayer().getPosition().x)
            );
        }

        int playerHealth = entityManager->getPlayer().getHealth();
        entityManager->updateAll(deltaTime.asSeconds());

        //if health has changed last update, update health UI
        if (playerHealth != entityManager->getPlayer().getHealth()) {
            interfaceManager->updateHealth(entityManager->getPlayer().getHealth());
        }

        //if any enemies are below the bottom of the screen, increment the score and send the new value to UI
        int count = entityManager->getOutOfBoundsCount();
        if (count > 0) {
            score += SCORE_PER_ENEMY[stage] * count;
            interfaceManager->updateScore(score);

            /*if (stage < SCORE_THRESHOLD.size() && score > SCORE_THRESHOLD.at(stage)) {
                stage++;
            }*/
        }
    }

    else if (state == "lose") {
        timer += deltaTime.asSeconds();
        if (timer >= 3.0f) {
            switchState("start");
            timer = .0f;
        }
    }
}

void GameManager::stateExit() {
    if (state == "splash") {
        interfaceManager->clearImages();
    }

    else if (state == "start") {
        interfaceManager->clearImages();
    }

    else if (state == "play") {
        entityManager->clearAll();
        interfaceManager->clearHealth();
        interfaceManager->clearImages();
    }

    else if (state == "lose") {
        interfaceManager->clearScore();
        interfaceManager->clearImages();
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
