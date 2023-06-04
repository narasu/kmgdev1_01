#include "Managers.h"
#pragma once

class InterfaceManager {
public:
    explicit InterfaceManager(std::shared_ptr<TextureManager> _textureManager);
    void initializeScore();
    void updateScore(int _score);
    void updateHealth(int _health);
    std::vector<std::reference_wrapper<sf::Sprite>> getSprites();

private:
    std::shared_ptr<TextureManager> textureManager;
    std::vector<sf::Sprite> health;
    std::vector<std::unique_ptr<sf::Sprite>> score;
    sf::Sprite title;
    sf::Sprite splash;
    sf::Sprite number;
    int numberWidth = 7;
    int textureMargin = 1;
    int spacing = 2;
};

