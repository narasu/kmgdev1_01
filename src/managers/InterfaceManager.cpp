//
// Created by Yamada on 4-6-2023.
//

#include "Managers.h"
#include "../GameData.h"
#include "InterfaceManager.h"


InterfaceManager::InterfaceManager(std::shared_ptr<TextureManager> _textureManager) : textureManager(_textureManager){

}

void InterfaceManager::initializeScoreAndHealth(Vector2<int> _offset) {
    baseOffset = _offset;
    for (int i=0; i<6; i++) {
        auto s = std::make_unique<sf::Sprite>(*textureManager->getTexture("numbers"));
        s->setTextureRect(sf::IntRect(0, 0, numberWidth, 7));
        s->setPosition(baseOffset.x + 45.0f + (numberWidth + spacing) * i, baseOffset.y);
        score.emplace_back(std::move(s));
    }
    for (int i=0; i<HEALTH; i++) {
        auto s = std::make_unique<sf::Sprite>(*textureManager->getTexture("heart"));
        s->setPosition(VIEWPORT_WIDTH - baseOffset.x - (s->getTexture()->getSize().x) * (i + 1) - spacing * i, baseOffset.y);
        health.emplace_back(std::move(s));
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

void InterfaceManager::showFinalScore() {
    //bool nReached = false;
    int i=0;
    for (auto it = score.begin() ; it < score.end(); it++) {
        (*it)->setPosition(VIEWPORT_WIDTH*0.5f + (numberWidth + spacing) * i, VIEWPORT_HEIGHT *0.5f);
        i++;
        /*if (!nReached && (*it)->getTextureRect().left == 0 && score.size() > 1) {
            it = score.erase(it);
            nReached = true;
        }
        else {
            i++;
        }*/
    }
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
        auto s = std::make_unique<sf::Sprite>(*textureManager->getTexture("heart"));
        s->setPosition(VIEWPORT_WIDTH - baseOffset.x - (s->getLocalBounds().width + spacing) * (h+1) + spacing, baseOffset.y);
        health.emplace_back(std::move(s));
        h-=1;
    }
}

std::vector<std::reference_wrapper<sf::Sprite>> InterfaceManager::getSprites() {
    std::vector<std::reference_wrapper<sf::Sprite>> sprites;
    for (auto & it : score) {
        sprites.emplace_back(*it);
    }
    for (auto & it : health) {
        sprites.emplace_back(*it);
    }
    for (auto & it : images) {
        sprites.emplace_back(*it);
    }
    return sprites;
}

void InterfaceManager::displayImage(std::string _texture, Vector2<float> _position, bool _centered) {
    auto s = std::make_unique<sf::Sprite>(*textureManager->getTexture(_texture));
    if (_centered) {
        _position -= Vector2<float>(s->getLocalBounds().width*0.5f, s->getLocalBounds().height*0.5f);
    }
    s->setPosition(_position.toSFML());
    images.emplace_back(std::move(s));
}

void InterfaceManager::clearImages() {
    images.clear();
}

void InterfaceManager::clearHealth() {
    health.clear();
}

void InterfaceManager::clearScore() {
    score.clear();
}


