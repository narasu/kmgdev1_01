//
// Created by Yamada on 25-5-2023.
//

#include "TextureManager.h"

TextureManager::TextureManager() {
    textureMap = std::map<std::string, sf::Texture*> {
        { "splash_screen", newTexture("assets/sprites/splash_screen.png") },
        { "title", newTexture("assets/sprites/title.png") },
        { "player", newTexture("assets/sprites/player.png") },
        { "grass", newTexture("assets/sprites/grass.png") },
        { "enemy01", newTexture("assets/sprites/enemy_crustachnid_sheet.png") },
        { "enemy02", newTexture("assets/sprites/enemy_decaying_mutant_sheet.png") },
        { "enemy03", newTexture("assets/sprites/enemy_macrobe_sheet.png") }
    };
}
/*

TextureManager::TextureManager(const TextureManager &_entity) {

}

TextureManager &TextureManager::operator=(const TextureManager &_entity) {

}
*/
TextureManager::~TextureManager() {
    for (auto i : textureMap) {
        delete i.second;
        i.second=nullptr;
    }
}


sf::Texture *TextureManager::newTexture(const std::string& _path) {
    sf::Texture* texture = new sf::Texture();
    if (texture->loadFromFile(_path)) {
        return texture;
    }
    //if loading the file was unsuccessful, delete the pointer we just made
    delete(texture);
    texture = nullptr;
    return texture;
}

sf::Texture *TextureManager::getTexture(const std::string& _name) {

    if (auto search = textureMap.find(_name); search == textureMap.end()) {
        return nullptr;
    }
    if (!textureMap[_name]) {
        return nullptr;
    }
    return textureMap[_name];
}
