#include <IEntity.h>
#pragma once

class Entity : public IEntity {
public:
    Entity();
    virtual ~Entity();
    void update() override;
    sf::Sprite getSprite() override;
protected:
//    std::string getTexturePath();
//    void initializeTexture();
//    sf::Texture* texture;
//    sf::Sprite* sprite;
};