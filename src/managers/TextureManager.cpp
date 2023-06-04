#include "Managers.h"

//TODO: Re-implement assignment operator and copy constructor

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
    return nullptr;
}

TextureManager::TextureManager(const TextureManager &_textureManager) {
    if (this == &_textureManager) {
        return;
    }
    //textureMap = std::map<std::string, std::shared_ptr<sf::Texture>>(copyTextureMap(_textureManager.textureMap));
}

TextureManager &TextureManager::operator=(const TextureManager &_textureManager) {
    if (this == &_textureManager) {
        return *this;
    }
    //textureMap = std::map<std::string, std::shared_ptr<sf::Texture>>(copyTextureMap(_textureManager.textureMap));
    return *this;
}

TextureManager::~TextureManager() {
    /*for (std::map<std::string, std::shared_ptr<sf::Texture>>::const_iterator it = textureMap->begin(); it != textureMap->end(); ++it) {
        delete (*it).second;
    }*/
    textureMap.clear();
}

std::map<std::string, std::shared_ptr<sf::Texture>> TextureManager::copyTextureMap(std::map<std::string, std::shared_ptr<sf::Texture>> &_map) {
    std::map<std::string, std::shared_ptr<sf::Texture>> m;
    for (auto it = _map.begin(); it != _map.end(); ++it) {
        m.insert(
                std::map<std::string, std::shared_ptr<sf::Texture>>::value_type(
                        it->first, _map.at(it->first))
        );
    }
    return m;
}
