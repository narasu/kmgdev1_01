#include <SFML/Graphics.hpp>
#include <list>
#include <cstdlib>
#include "Player.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "Spawner.h"

int main()
{
    //game initialization
    sf::RenderWindow* window;
    sf::Vector2<int> viewportSize(320,180);
    window = new sf::RenderWindow(sf::VideoMode(viewportSize.x, viewportSize.y), "Alien Exile");
    sf::Vector2<int> windowPosition(0,0);
    sf::Vector2<unsigned int> windowSize(1280,720);
    window->setSize(windowSize);
    window->setPosition(windowPosition);
    window->setFramerateLimit(60);
    sf::Clock deltaClock = sf::Clock();
    //std::srand(26);
    TextureManager* textureManager = new TextureManager();
    EntityManager* entityManager = new EntityManager();
    Spawner spawner = Spawner(viewportSize.x, 2.0f);

    //spawn player
    entityManager->addEntity(new Player(textureManager->getTexture("player")));

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
            entityManager->addEntity(
                    spawner.spawnEnemy(textureManager->getTexture("enemy0" + std::to_string(random123)))
                    );
        }
        entityManager->updateAll(deltaTime.asSeconds(), float(viewportSize.y));
        //end game logic calls

        //begin draw calls
        window->clear(sf::Color::Black);
        std::list<Entity*> entities = entityManager->getEntities();
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