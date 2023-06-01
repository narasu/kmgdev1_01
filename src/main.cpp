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
    auto textureManager = std::make_unique<TextureManager>();
    auto player = std::make_shared<Player>(*textureManager->getTexture("player"), Rect<float>(.0f, 2.0f, 6.0f, 8.0f));
    auto entityManager = std::make_unique<EntityManager>(player);
    Spawner spawner = Spawner(VIEWPORT_WIDTH, 3.0f);


    while (window->isOpen()) {
        //inputs to close window
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) window->close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window->close();
        }

        //begin game logic calls
        sf::Time deltaTime = deltaClock.restart();
        if (spawner.updateTimer(deltaTime.asSeconds())) {
            int random123 = rand() % 3 + 1;
            std::string randomEnemy = "enemy0" + std::to_string(random123);
            std::shared_ptr<Enemy> e = spawner.spawnEnemy(
                    *textureManager->getTexture(randomEnemy),
                    player->getPosition().x);

            entityManager->addEnemy(e);
        }
        entityManager->updateAll(deltaTime.asSeconds(), float(VIEWPORT_HEIGHT));
        //end game logic calls

        //begin draw calls
        window->clear(sf::Color::Black);
        for (auto & it : entityManager->getEntityList()) {
            window->draw(it->getSprite());
        }
        window->display();
        //end draw calls
    }

    return 0;
}