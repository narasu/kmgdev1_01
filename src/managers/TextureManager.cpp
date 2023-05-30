#include "Managers.h"

TextureManager::TextureManager() {

    textureMap = new std::map<std::string, sf::Texture*> {
        { "splash_screen", newTexture("assets/sprites/splash_screen.png") },
        { "title", newTexture("assets/sprites/title.png") },
        { "player", newTexture("assets/sprites/player.png") },
        { "grass", newTexture("assets/sprites/grass.png") },
        { "enemy01", newTexture("assets/sprites/enemy_crustachnid_sheet.png") },
        { "enemy02", newTexture("assets/sprites/enemy_decaying_mutant_sheet.png") },
        { "enemy03", newTexture("assets/sprites/enemy_macrobe_sheet.png") }
    };
}

sf::Texture *TextureManager::getTexture(const std::string& _name) {
    if (auto search = textureMap->find(_name); search == textureMap->end()) {
        return nullptr;
    }
    return textureMap->at(_name);
}

sf::Texture *TextureManager::newTexture(const std::string& _path) {
    sf::Texture *texture = new sf::Texture();
    if (texture->loadFromFile(_path)) {
        return texture;
    }
    //if loading the file was unsuccessful, delete the pointer we just made
    delete texture;
    texture = nullptr; // <- not sure if necessary? does this pointer stop existing at the end of the method?
    return nullptr;
}

TextureManager::TextureManager(const TextureManager &_textureManager) {
    if (this == &_textureManager) {
        return;
    }
    textureMap = new std::map<std::string, sf::Texture *>(copyTextureMap(*_textureManager.textureMap));
}

TextureManager &TextureManager::operator=(const TextureManager &_textureManager) {
    if (this == &_textureManager) {
        return *this;
    }
    textureMap = new std::map<std::string, sf::Texture *>(copyTextureMap(*_textureManager.textureMap));
    return *this;
}

TextureManager::~TextureManager() {
    for (std::map<std::string, sf::Texture *>::const_iterator it = textureMap->begin(); it != textureMap->end(); ++it) {
        delete (*it).second;
    }
    textureMap->clear();
}

std::map<std::string, sf::Texture *> TextureManager::copyTextureMap(std::map<std::string, sf::Texture *> &_map) {
    std::map<std::string, sf::Texture *> m;
    for (std::map<std::string, sf::Texture *>::const_iterator it = _map.begin(); it != _map.end(); ++it) {
        m.insert(
                std::map<std::string, sf::Texture *>::value_type(
                        it->first, new sf::Texture(*_map.at(it->first))
                        )
        );
    }
    return m;
}
