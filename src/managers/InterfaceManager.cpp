#include "Managers.h"
#include "../GameData.h"

InterfaceManager::InterfaceManager(const InterfaceManager &_interfaceManager) {
    if (this == &_interfaceManager) {
        return;
    }
    textureManager = _interfaceManager.textureManager;
    for (auto &it : _interfaceManager.health) {
        health.emplace_back(std::make_unique<sf::Sprite>(*it));
    }
    for (auto &it : _interfaceManager.score) {
        score.emplace_back(std::make_unique<sf::Sprite>(*it));
    }
    for (auto &it : _interfaceManager.images) {
        images.emplace_back(std::make_unique<sf::Sprite>(*it));
    }
}

InterfaceManager &InterfaceManager::operator=(const InterfaceManager &_interfaceManager) {
    if (this == &_interfaceManager) {
        return *this;
    }

    textureManager = _interfaceManager.textureManager;
    clearHealth();
    clearImages();
    clearScore();
    for (auto &it : _interfaceManager.health) {
        health.emplace_back(std::make_unique<sf::Sprite>(*it));
    }
    for (auto &it : _interfaceManager.score) {
        score.emplace_back(std::make_unique<sf::Sprite>(*it));
    }
    for (auto &it : _interfaceManager.images) {
        images.emplace_back(std::make_unique<sf::Sprite>(*it));
    }
}

void InterfaceManager::initializeScoreAndHealth(Vector2<int> _offset) {
    baseOffset = _offset;

    // initialize 6 digits at value 0
    for (int i=0; i<6; i++) {
        auto s = std::make_unique<sf::Sprite>(*textureManager->getTexture("numbers"));
        s->setTextureRect(sf::IntRect(0, 0, numberWidth, numberWidth));
        s->setPosition(baseOffset.x + 45.0f + (numberWidth + spacing) * i, baseOffset.y);
        score.emplace_back(std::move(s));
    }

    // initialize heart for each point of health
    for (int i=0; i < START_HEALTH; i++) {
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

        // split digits of score value, back to front
        if (i > 0) {
            n = _score / static_cast<int>(pow(10, i)) % 10;
        }
        else {
            n = _score % 10;
        }

        // set current sprite to correct digit
        Rect<int> r = Rect<int>((numberWidth + textureMargin) * n, 0, numberWidth, numberWidth);
        (*it)->setTextureRect(r.toSFML());
        i++;
    }
}

void InterfaceManager::showFinalScore() {
    // move the score to the center of the screen
    int i=0;
    for (auto it = score.begin() ; it < score.end(); it++) {
        (*it)->setPosition(roundf(VIEWPORT_WIDTH*0.5f) + (numberWidth + spacing) * i, roundf(VIEWPORT_HEIGHT *0.5f));
        i++;
    }
}

void InterfaceManager::updateHealth(int _health) {
    int h = _health - health.size();
    if (h == 0) {
        return;
    }
    //for each health lost, remove a heart from the vector
    while (h < 0) {
        health.pop_back();
        h+=1;
    }
    //for each health gained, add a heart (currently unused)
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

void InterfaceManager::displayImage(const std::string& _texture, Vector2<float> _position, bool _centered) {
    auto s = std::make_unique<sf::Sprite>(*textureManager->getTexture(_texture));
    if (_centered) {
        _position -= Vector2<float>(s->getLocalBounds().width*0.5f, s->getLocalBounds().height*0.5f);
    }
    s->setPosition(_position.toSFML());
    images.emplace_back(std::move(s));
}


