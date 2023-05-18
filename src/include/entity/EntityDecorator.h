#include <IEntity.h>
#pragma once

class EntityDecorator : public IEntity {
public:
    EntityDecorator(IEntity* _entity);
    virtual void update();
    virtual sf::Sprite getSprite();
    virtual ~EntityDecorator();
protected:
    IEntity* entity;
};