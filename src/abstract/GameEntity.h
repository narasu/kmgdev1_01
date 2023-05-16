#include <SFML/Graphics.hpp>

class GameEntity : public sf::Sprite {
protected:
    virtual std::string getTexturePath() = 0;
    virtual void initializeTexture();
    sf::Texture* texture;
public:
    GameEntity();

    virtual ~GameEntity();
};