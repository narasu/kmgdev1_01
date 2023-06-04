//
// Created by Yamada on 4-6-2023.
//

#include "Managers.h"
#include "../GameData.h"
#include "InterfaceManager.h"


InterfaceManager::InterfaceManager(std::shared_ptr<TextureManager> _textureManager) : textureManager(_textureManager){

}

void InterfaceManager::initializeScore() {
    float baseOffset = 10.0f;
    for (int i=0; i<6; i++) {
        auto s = std::make_unique<sf::Sprite>(*textureManager->getTexture("numbers"));
        s->setTextureRect(sf::IntRect(0, 0, numberWidth, 7));
        s->setPosition(baseOffset + (numberWidth + spacing) * i - spacing, baseOffset);
        score.emplace_back(std::move(s));
    }
}

void InterfaceManager::updateScore(int _score) {
    int tempScore = _score;
    int length = 1;
    while ( tempScore /= 10) {
        length++;
    }

    int i = 0;
    for (auto it = score.end() - 1; it >= score.begin(); it--) {
        int n = 0;
        if (i > 0) {
            n = _score / static_cast<int>(pow(10, i)) % 10;
        }
        else {
            n = _score % 10;
        }

        sf::IntRect r = sf::IntRect((numberWidth + textureMargin) * n, 0, numberWidth, numberWidth);
        (*it)->setTextureRect(r);
        i++;
    }
}

void InterfaceManager::updateHealth(int _health) {
    int h = health.size() - _health;
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

std::vector<std::reference_wrapper<sf::Sprite>> InterfaceManager::getSprites() {
    std::vector<std::reference_wrapper<sf::Sprite>> sprites;
    for (auto & it : score) {
        sprites.push_back(*it);
    }
    return sprites;
}

