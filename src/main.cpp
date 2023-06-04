#include <SFML/Graphics.hpp>

#include <iostream>
#include "hiro/Hiro.h"
#include "managers/Managers.h"
#include "GameData.h"

using namespace Hiro;
int main()
{
    //game initialization
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(VIEWPORT_WIDTH, VIEWPORT_HEIGHT), "Alien Exile");
    Vector2<unsigned int> windowSize(1280, 720);
    Vector2<int> windowPosition(sf::VideoMode::getDesktopMode().width/2 - windowSize.x/2, sf::VideoMode::getDesktopMode().height/2 - windowSize.y/2);
    window->setSize(windowSize.toSFML());
    window->setPosition(windowPosition.toSFML());
    window->setFramerateLimit(60);

    auto textureManager = std::make_shared<TextureManager>();
    auto entityManager = std::make_shared<EntityManager>();
    auto interfaceManager = std::make_shared<InterfaceManager>(textureManager);
    auto gameManager = std::make_unique<GameManager>(textureManager, entityManager, interfaceManager);


    while (window->isOpen()) {
        //inputs to close window
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) window->close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window->close();
        }

        gameManager->stateUpdate();

        window->clear(sf::Color::Black);

        for (auto & it : entityManager->getSprites()) {
            window->draw(it);
        }

        for (auto &it : interfaceManager->getSprites()) {
            window->draw(it);
        }

        window->display();
    }

    return 0;
}