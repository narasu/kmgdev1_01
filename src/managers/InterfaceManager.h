#include "Managers.h"
#pragma once

class InterfaceManager {
public:
    InterfaceManager();
    void updateScore(int _score);
    void updateHealth(int _health);
    sf::Text &getScoreText();
    sf::Text &getCenterText();
private:
    sf::Font font;
    sf::Text scoreText;
    sf::Text centerText;
    std::vector<sf::Sprite> health;
    sf::Sprite title;
    sf::Sprite splash;
};

