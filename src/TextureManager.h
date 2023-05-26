#include <SFML/Graphics.hpp>
#pragma once

class TextureManager {
public:
    TextureManager();
    TextureManager(const TextureManager& _textureManager); //copy constructor
    TextureManager& operator=(const TextureManager& _entity); //assignment operator
    ~TextureManager();
    sf::Texture *newTexture(const std::string& _path);
    sf::Texture *getTexture(const std::string& _name);
private:
    std::map<std::string, sf::Texture*> *textureMap;
    std::map<std::string, sf::Texture*> copyTextureMap(std::map<std::string, sf::Texture *> &_map);
};