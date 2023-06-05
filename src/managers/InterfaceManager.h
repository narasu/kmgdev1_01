//HUD, text and title images
//note: all text is sprites as I couldn't get SFML to render text without anti-aliasing

#include "Managers.h"
#pragma once

class InterfaceManager {
public:
    explicit InterfaceManager(std::shared_ptr<TextureManager> _textureManager);
    void initializeScoreAndHealth(Vector2<int> _offset);
    void updateScore(int _score);
    void showFinalScore();
    void updateHealth(int _health);
    void displayImage(std::string _texture, Vector2<float> _position, bool _centered = true);
    void clearImages();
    void clearHealth();
    void clearScore();
    std::vector<std::reference_wrapper<sf::Sprite>> getSprites();

private:
    std::shared_ptr<TextureManager> textureManager;
    std::vector<std::unique_ptr<sf::Sprite>> health;
    std::vector<std::unique_ptr<sf::Sprite>> score;
    std::vector<std::unique_ptr<sf::Sprite>> images;
    Vector2<int> baseOffset = Vector2<int>(20, 5);
    int numberWidth = 7;
    int textureMargin = 1;
    int spacing = 2;
};

