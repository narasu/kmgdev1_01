// Executive class that handles game states with a basic finite state machine
// as well as delegating between other managers

#include "Managers.h"
#include "../GameData.h"

GameManager::GameManager(std::shared_ptr<TextureManager> _textureManager, std::shared_ptr<EntityManager> _entityManager, std::shared_ptr<InterfaceManager> _interfaceManager) :
textureManager(_textureManager), entityManager(_entityManager), interfaceManager(_interfaceManager) {
    spawner = std::make_unique<Spawner>(textureManager, entityManager);
    audioManager = std::make_unique<AudioManager>();
    state = SplashState;
    stateEnter();
}

void GameManager::stateEnter() {
    if (state == SplashState) {
        interfaceManager->displayImage("splash", Vector2<float>(VIEWPORT_WIDTH*0.5f, VIEWPORT_HEIGHT*0.5f));
    }

    else if (state == StartState) {
        spawner->setTimerActive(GRASS, true);

        entityManager->setPlayer(
                std::make_unique<Player>(*textureManager->getTexture("player"), BOUNDS.at("player"))
                );
        interfaceManager->displayImage("title", Vector2<float>(VIEWPORT_WIDTH * 0.5f, 35.0f));
        interfaceManager->displayImage("start_text", Vector2<float>(VIEWPORT_WIDTH * 0.5f, VIEWPORT_HEIGHT * 0.5f + 20.0f));
    }

    else if (state == PlayState) {
        if (stage == 0) {
            auto offset = Vector2<int>(6,3);
            interfaceManager->displayImage("score", Vector2<float>(offset.x, offset.y), false);
            interfaceManager->initializeScoreAndHealth(offset);
            audioManager->playMusic();
        }
        spawner->setTimerActive(ENEMY, true);
    }

    else if (state == StageUpState) {
        spawner->setTimerActive(ENEMY, false);
    }

    else if (state == LoseState) {
        spawner->setTimerActive(GRASS, false);
        spawner->setTimerActive(ENEMY, false);

        audioManager->stopMusic();
        entityManager->clearAll();
        interfaceManager->clearHealth();
        interfaceManager->clearImages();

        audioManager->playSound(LoseSound);
        interfaceManager->displayImage("end_text", Vector2<float>(VIEWPORT_WIDTH * 0.5f, VIEWPORT_HEIGHT * 0.5f - 12.0f));
        interfaceManager->displayImage("score", Vector2<float>(VIEWPORT_WIDTH * 0.5f - 50.0f, VIEWPORT_HEIGHT * 0.5f), false);
        interfaceManager->showFinalScore();
    }
}

void GameManager::stateUpdate() {
    auto deltaTime = deltaClock.restart();

    if (state == SplashState) {
        timer += deltaTime.asSeconds();
        if (timer >= 3.0f) {
            switchState(StartState);
            timer = .0f;
            return;
        }
    }

    else if (state == StartState) {

        spawner->update(stage, deltaTime.asSeconds());
        entityManager->updateAll(deltaTime.asSeconds());

        // go to play state when the player moves
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            switchState(PlayState);
            return;
        }
    }

    else if (state == StageUpState) {
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
            switchState(PlayState);
        }

    }

    else if (state == PlayState) {
        if (entityManager->getPlayer().isDestroyed()) {
            switchState(LoseState);
            return;
        }
        spawner->update(stage, deltaTime.asSeconds(), entityManager->getPlayer().getPosition().x);
        if (spawner->isEnemySpawned()) {
            std::cout << "enemy is spawned " << std::endl;
            audioManager->playSound(EnemySpawnSound);
            spawner->spawnCallback();
        }


        // temp store pre-update player health
        int playerHealth = entityManager->getPlayer().getHealth();

        entityManager->updateAll(deltaTime.asSeconds());

        if (entityManager->isPlayerHit()) {
            std::cout << "player is hit " << std::endl;
            audioManager->playSound(PlayerHitSound);
            entityManager->playerHitCallback();
        }

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
                switchState(StageUpState);
            }
        }
    }

    else if (state == LoseState) {
        timer += deltaTime.asSeconds();
        if (timer >= 5.0f) {
            switchState(StartState);
            timer = .0f;
        }
    }
}

void GameManager::stateExit() {
    if (state == SplashState) {
        interfaceManager->clearImages();
    }

    else if (state == StartState) {
        interfaceManager->clearImages();
    }

    else if (state == LoseState) {
        interfaceManager->clearScore();
        interfaceManager->clearImages();
    }
}

void GameManager::switchState(StateType _state) {
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
    state = _gameManager.state;
}

GameManager &GameManager::operator=(const GameManager &_gameManager) {
    if (this == &_gameManager) {
        return *this;
    }
    spawner = std::make_unique<Spawner>(*_gameManager.spawner);
    textureManager = _gameManager.textureManager;
    entityManager = _gameManager.entityManager;
    interfaceManager = _gameManager.interfaceManager;
    state = _gameManager.state;
    return *this;
}
