#include <SFML/Graphics.hpp>
#include <list>
#include <cstdlib>
#include <iostream>
#include "hiro/Hiro.h"
#include "managers/Managers.h"
#include "Player.h"
#include "Spawner.h"

const int VIEWPORT_WIDTH = 320;
const int VIEWPORT_HEIGHT = 180;

using namespace Hiro;
int main()
{
    //game initialization
    sf::RenderWindow* window;
    window = new sf::RenderWindow(sf::VideoMode(VIEWPORT_WIDTH, VIEWPORT_HEIGHT), "Alien Exile");
    Vector2<int> windowPosition(0, 0);

    Vector2<unsigned int> windowSize(1280, 720);
    window->setSize(windowSize.toSFML());
    window->setPosition(windowPosition.toSFML());
    window->setFramerateLimit(60);
    sf::Clock deltaClock = sf::Clock();
    //std::srand(26);
    TextureManager* textureManager = new TextureManager();
    EntityManager* entityManager = new EntityManager();
    Spawner spawner = Spawner(VIEWPORT_WIDTH, 3.0f);

    //spawn player
    Player* player = new Player(textureManager->getTexture("player"));
    entityManager->addEntity(player);

    while (window->isOpen()) {
        //inputs to close window
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) window->close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window->close();
        }

        sf::Time deltaTime = deltaClock.restart();
        if (spawner.updateTimer(deltaTime.asSeconds())) {
            int random123 = rand() % 3 + 1;
            entityManager->addEntity(
                    spawner.spawnEnemy(
                            textureManager->getTexture("enemy0" + std::to_string(random123)),
                            player->getPosition().x)
                    );
        }
        entityManager->updateAll(deltaTime.asSeconds(), float(VIEWPORT_HEIGHT));
        //end game logic calls

        //begin draw calls
        window->clear(sf::Color::Black);
        std::list<Entity*> entities = entityManager->getEntityList();
        for (std::list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); ++it) {
            window->draw((*it)->getSprite());
        }
        window->display();
        //end draw calls
    }

    //cleanup
    delete entityManager;
    entityManager = nullptr;
    delete textureManager;
    textureManager = nullptr;
    return 0;
}