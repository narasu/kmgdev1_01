#include "EntityDecorator.h"

#pragma once
class AnimationDecorator : public EntityDecorator {
public:
    AnimationDecorator(IEntity* _entity);
    void update() override;

private:
    int frameRate;
    sf::Vector2<int> cells;
    sf::Vector2<int> cellSize;
};