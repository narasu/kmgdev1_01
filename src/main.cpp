#include <SFML/Graphics.hpp>
#include <list>
#include "Player.h"
#include "Enemy.h"
#include "TextureManager.h"

int main()
{
    sf::RenderWindow* window;
    window = new sf::RenderWindow(sf::VideoMode(320, 180), "Alien Exile");
    sf::Vector2<int> windowPosition(0,0);
    sf::Vector2<unsigned int> windowSize(1280,720);
    window->setSize(windowSize);
    window->setPosition(windowPosition);
    window->setFramerateLimit(60);
    sf::Clock deltaClock = sf::Clock();

    TextureManager* textureManager = new TextureManager();

    std::list<Entity*> entityList;
    Player* player = new Player(textureManager->getTexture("player"));
    entityList.push_back(player);
    Enemy* enemy = new Enemy(textureManager->getTexture("enemy01"));
    entityList.push_back(enemy);


    while (window->isOpen()) {

        sf::Event event;

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) window->close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window->close();

        }

        window->clear(sf::Color::Black);
        sf::Time deltaTime = deltaClock.restart();
        for (Entity* entity : entityList) {
            entity->update(deltaTime.asSeconds());
            window->draw(entity->getSprite());
        }

        window->display();
    }

    for (Entity* entity : entityList) {
        delete entity;
        entity = nullptr;
    }
    delete textureManager;
    textureManager = nullptr;
    return 0;
}