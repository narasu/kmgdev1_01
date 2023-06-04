//
// Created by Yamada on 4-6-2023.
//

#include "Managers.h"
#include "../GameData.h"

InterfaceManager::InterfaceManager() {
    font.loadFromFile("assets/ponde__.ttf");

    scoreText.setFont(font);
    scoreText.setCharacterSize(10);
    scoreText.setFillColor(sf::Color::White);

    centerText.setFont(font);
    centerText.setCharacterSize(10);
    centerText.setFillColor(sf::Color::White);
    centerText.setPosition(static_cast<float>(VIEWPORT_WIDTH)*0.5f, static_cast<float>(VIEWPORT_HEIGHT)*0.5f);
    centerText.setString(START_TEXT);
}

void InterfaceManager::updateScore(int _score) {
    scoreText.setString("SCORE " + std::to_string(_score));
}

void InterfaceManager::updateHealth(int _health) {
    int h = _health - health.size();
    if (h == 0) {
        return;
    }
    while (h < 0) {
        health.pop_back();
        h+=1;
    }
    while (h > 0) {

        //health.emplace_back(sf::)
        h-=1;
    }
}

sf::Text &InterfaceManager::getScoreText() {
    return scoreText;
}

sf::Text &InterfaceManager::getCenterText() {
    return centerText;
}
