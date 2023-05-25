#include <SFML/Graphics.hpp>

class TextureManager {
public:
    TextureManager();
    /*TextureManager(const TextureManager& _entity); //copy constructor
    TextureManager& operator=(const TextureManager& _entity); //assignment operator*/
    ~TextureManager();
    //void initializeTexture(std::string _path);
    sf::Texture *newTexture(const std::string& _path);
    sf::Texture *getTexture(const std::string& _name);
private:
    std::map<std::string, sf::Texture*> textureMap;
};