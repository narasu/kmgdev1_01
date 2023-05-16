#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
    sf::RenderWindow* window;
    window = new sf::RenderWindow(sf::VideoMode(320, 180), "SFML");
    sf::Vector2<int> windowPosition(0,0);
    sf::Vector2<unsigned int> windowSize(1280,720);
    window->setSize(windowSize);
    window->setPosition(windowPosition);
    window->setFramerateLimit(60);
    Player* player = new Player();



    while (window->isOpen()) {

        sf::Event event;

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) window->close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window->close();

        }

        player->handleMovement();

        window->clear(sf::Color::Black);
        window->draw(*player);
        window->display();
    }
    return 0;
}