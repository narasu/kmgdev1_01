// This class creates and manages all textures and passes pointers any instance of Entity

#include "Managers.h"
#pragma once

class TextureManager {
public:
    TextureManager();
    TextureManager(const TextureManager& _textureManager); //copy constructor
    TextureManager& operator=(const TextureManager& _entity); //assignment operator
    ~TextureManager();
    std::shared_ptr<sf::Texture> newTexture(const std::string& _path);
    std::shared_ptr<sf::Texture> getTexture(const std::string& _name);
private:
    std::map<std::string, std::shared_ptr<sf::Texture>> textureMap;
    std::map<std::string, std::shared_ptr<sf::Texture>> copyTextureMap(std::map<std::string, std::shared_ptr<sf::Texture>> &_map);
};