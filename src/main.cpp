#include <SFML/Graphics.hpp>
#include <list>
#include <cstdlib>
#include <iostream>
#include "hiro/Hiro.h"
#include "managers/Managers.h"
#include "Player.h"
#include "Spawner.h"
#include "GameData.h"


using namespace Hiro;
int main()
{
    //game initialization
    sf::RenderWindow* window;
    window = new sf::RenderWindow(sf::VideoMode(VIEWPORT_WIDTH, VIEWPORT_HEIGHT), "Alien Exile");
    Vector2<unsigned int> windowSize(1280, 720);
    Vector2<int> windowPosition(sf::VideoMode::getDesktopMode().width/2 - windowSize.x/2, sf::VideoMode::getDesktopMode().height/2 - windowSize.y/2);
    window->setSize(windowSize.toSFML());
    window->setPosition(windowPosition.toSFML());
    window->setFramerateLimit(60);
    sf::Clock deltaClock = sf::Clock();
    //std::srand(26);
    auto textureManager = std::make_unique<TextureManager>();
    auto entityManager = std::make_unique<EntityManager>(
            std::make_unique<Player>(*textureManager->getTexture("player"), Rect<float>(.0f, 2.0f, 6.0f, 8.0f))
            );
    auto spawner = Spawner(3.0f);

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
            entityManager->addEnemy(
                    spawner.spawnEnemy(
                        *textureManager->getTexture(randomEnemy),
                        collisionRects.at(randomEnemy),
                        entityManager->getPlayer().getPosition().x)
                    );
        }
        entityManager->updateAll(deltaTime.asSeconds());
        //end game logic calls

        //begin draw calls
        window->clear(sf::Color::Black);
        for (auto & it : entityManager->getSprites()) {
            window->draw(it);
        }
        window->display();
        //end draw calls
    }

    return 0;
}