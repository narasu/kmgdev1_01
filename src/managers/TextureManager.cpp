#include "Managers.h"

TextureManager::TextureManager() {

    textureMap = std::map<std::string, std::shared_ptr<sf::Texture>> {
        { "splash", newTexture("assets/ui/splash_screen.png") },
        { "title", newTexture("assets/ui/title.png") },
        { "start_text", newTexture("assets/ui/start_text.png") },
        { "end_text", newTexture("assets/ui/end_text.png") },
        { "score", newTexture("assets/ui/score.png") },
        { "numbers", newTexture("assets/ui/numbers.png") },
        { "heart", newTexture("assets/ui/heart.png") },
        { "player", newTexture("assets/entities/player.png") },
        { "grass", newTexture("assets/entities/grass.png") },
        { "enemy01", newTexture("assets/entities/enemy_crustachnid_sheet.png") },
        { "enemy02", newTexture("assets/entities/enemy_decaying_mutant_sheet.png") },
        { "enemy03", newTexture("assets/entities/enemy_macrobe_sheet.png") }
    };
}

std::shared_ptr<sf::Texture> TextureManager::getTexture(const std::string& _name) {
    if (auto search = textureMap.find(_name); search == textureMap.end()) {
        std::cout << "Could not find texture " + _name << std::endl;
        return nullptr;
    }
    return textureMap.at(_name);
}

std::shared_ptr<sf::Texture> TextureManager::newTexture(const std::string& _path) {
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile(_path)) {
        return texture;
    }
    // SFML already prints its own error message if loading fails
    return nullptr;
}

TextureManager::TextureManager(const TextureManager &_textureManager) {
    if (this == &_textureManager) {
        return;
    }
    for (auto & it : _textureManager.textureMap) {
        textureMap.insert(it);
    }
}

TextureManager &TextureManager::operator=(const TextureManager &_textureManager) {
    if (this == &_textureManager) {
        return *this;
    }
    for (auto & it : _textureManager.textureMap) {
        textureMap.insert(it);
    }
    return *this;
}