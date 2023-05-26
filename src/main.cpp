#include <SFML/Graphics.hpp>
#include <list>
#include "Player.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "Spawner.h"

int main()
{
    sf::RenderWindow* window;

    sf::Vector2<int> viewportSize(320,180);
    window = new sf::RenderWindow(sf::VideoMode(viewportSize.x, viewportSize.y), "Alien Exile");
    sf::Vector2<int> windowPosition(0,0);
    sf::Vector2<unsigned int> windowSize(1280,720);
    window->setSize(windowSize);
    window->setPosition(windowPosition);
    window->setFramerateLimit(60);
    sf::Clock deltaClock = sf::Clock();

    TextureManager* textureManager = new TextureManager();
    Spawner spawner = Spawner(viewportSize.x, 2.0f);

    std::list<Entity*> entityList;
    Player* player = new Player(textureManager->getTexture("player"));
    entityList.push_back(player);

    while (window->isOpen()) {

        sf::Event event;

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) window->close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window->close();

        }

        //game logic calls
        sf::Time deltaTime = deltaClock.restart();
        if (spawner.updateTimer(deltaTime.asSeconds())) {
            entityList.push_back(spawner.spawnEnemy(textureManager->getTexture("enemy01")));
        }
        for (Entity* entity : entityList) {
            entity->update(deltaTime.asSeconds());
        }
        //end game logic calls

        //draw calls
        window->clear(sf::Color::Black);
        for (Entity* entity : entityList) {
            window->draw(entity->getSprite());
        }
        //end draw calls

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