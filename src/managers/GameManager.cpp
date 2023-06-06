// Executive class that handles game states with a basic finite state machine

#include "Managers.h"
#include "../GameData.h"

//TODO: replace strings with enums
//TODO: IF I HAVE THAT MUCH TIME AND ENERGY i can separate the states into separate classes

GameManager::GameManager(std::shared_ptr<TextureManager> _textureManager, std::shared_ptr<EntityManager> _entityManager, std::shared_ptr<InterfaceManager> _interfaceManager) :
textureManager(_textureManager), entityManager(_entityManager), interfaceManager(_interfaceManager) {
    spawner = std::make_unique<Spawner>(textureManager, entityManager);
    state = "splash";
    stateEnter();
}

void GameManager::stateEnter() {
    if (state == "splash") {
        interfaceManager->displayImage("splash", Vector2<float>(VIEWPORT_WIDTH*0.5f, VIEWPORT_HEIGHT*0.5f));
    }

    else if (state == "start") {
        spawner->setTimerActive(GRASS, true);

        entityManager->setPlayer(
                std::make_unique<Player>(*textureManager->getTexture("player"), BOUNDS.at("player"))
                );
        interfaceManager->displayImage("title", Vector2<float>(VIEWPORT_WIDTH * 0.5f, 35.0f));
        interfaceManager->displayImage("start_text", Vector2<float>(VIEWPORT_WIDTH * 0.5f, VIEWPORT_HEIGHT * 0.5f + 20.0f));
    }

    else if (state == "play") {
        if (stage == 0) {
            auto offset = Vector2<int>(6,3);
            interfaceManager->displayImage("score", Vector2<float>(offset.x, offset.y), false);
            interfaceManager->initializeScoreAndHealth(offset);
        }
        spawner->setTimerActive(ENEMY, true);
    }

    else if (state == "lose") {
        spawner->setTimerActive(GRASS, false);
        spawner->setTimerActive(ENEMY, false);

        entityManager->clearAll();
        interfaceManager->clearHealth();
        interfaceManager->clearImages();

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

        spawner->update(stage, deltaTime.asSeconds());
        entityManager->updateAll(deltaTime.asSeconds());

        // go to play state when the player moves
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            switchState("play");
            return;
        }
    }

    else if (state == "stage_up") {
        spawner->update(stage, deltaTime.asSeconds());
        entityManager->updateAll(deltaTime.asSeconds());

        //if any enemies are below the bottom of the screen, increment the score and send the new value to UI
        int count = entityManager->getEnemyOutOfBoundsCount();
        if (count > 0) {
            score += SCORE_PER_ENEMY[stage] * count;
            interfaceManager->updateScore(score);
        }

        if (entityManager->getEnemies().empty()) {
            stage+=1;
            for (auto & it : entityManager->getGrass()) {
                it->setSpeedY(STAGE_SPEED[stage]);
            }
            spawner->setSpawnInterval(SpawnType::ENEMY, ENEMY_SPAWN_INTERVAL[stage]);
            spawner->setSpawnInterval(SpawnType::GRASS, GRASS_SPAWN_INTERVAL[stage]);
            switchState("play");
        }

    }

    else if (state == "play") {
        if (entityManager->getPlayer().isDestroyed()) {
            switchState("lose");
            return;
        }
        spawner->update(stage, deltaTime.asSeconds(), entityManager->getPlayer().getPosition().x);


        // temp store pre-update player health
        int playerHealth = entityManager->getPlayer().getHealth();

        entityManager->updateAll(deltaTime.asSeconds());

        //if health has changed last update, update health UI
        if (playerHealth != entityManager->getPlayer().getHealth()) {
            interfaceManager->updateHealth(entityManager->getPlayer().getHealth());
        }

        //if any enemies are below the bottom of the screen, increment the score and send the new value to UI
        int count = entityManager->getEnemyOutOfBoundsCount();
        if (count > 0) {
            score += SCORE_PER_ENEMY[stage] * count;
            interfaceManager->updateScore(score);

            if (stage < SCORE_THRESHOLD.size() && score >= SCORE_THRESHOLD.at(stage)) {
                switchState("stage_up");
            }
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
        spawner->setTimerActive(ENEMY, false);
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

GameManager::GameManager(const GameManager &_gameManager) {
    if (this == &_gameManager) {
        return;
    }
    spawner = std::make_unique<Spawner>(*_gameManager.spawner);
    textureManager = _gameManager.textureManager;
    entityManager = _gameManager.entityManager;
    interfaceManager = _gameManager.interfaceManager;
}

GameManager &GameManager::operator=(const GameManager &_gameManager) {
    if (this == &_gameManager) {
        return *this;
    }
    spawner = std::make_unique<Spawner>(*_gameManager.spawner);
    textureManager = _gameManager.textureManager;
    entityManager = _gameManager.entityManager;
    interfaceManager = _gameManager.interfaceManager;
    return *this;
}
