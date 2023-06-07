#include <SFML/Graphics.hpp>

#include <iostream>
#include "hiro/Hiro.h"
#include "managers/Managers.h"
#include "GameData.h"
#include "Sound.h"

using namespace Hiro;
int main()
{
    //game initialization
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(VIEWPORT_WIDTH, VIEWPORT_HEIGHT), "Alien Exile");
    Vector2<unsigned int> windowSize(540, 960);
    Vector2<int> windowPosition(sf::VideoMode::getDesktopMode().width/2 - windowSize.x/2, 0);
    window->setSize(windowSize.toSFML());
    window->setPosition(windowPosition.toSFML());
    window->setFramerateLimit(60);
    sf::RectangleShape r = sf::RectangleShape(Vector2<float>(VIEWPORT_WIDTH, HUD_HEIGHT).toSFML());

    auto textureManager = std::make_shared<TextureManager>();
    auto interfaceManager = std::make_shared<InterfaceManager>(textureManager);
    auto entityManager = std::make_shared<EntityManager>();
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

        for (const auto & it : entityManager->getSprites()) {
            window->draw(it);
        }


        /*r.setFillColor(sf::Color::Black);
        window->draw(r);*/

        for (auto &it : interfaceManager->getSprites()) {
            window->draw(it);
        }

        window->display();
    }

    return 0;
}