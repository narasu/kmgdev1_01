#include "EntityDecorator.h"
#include <iostream>
#pragma once
EntityDecorator::EntityDecorator(IEntity* _entity) : entity(_entity) {
    std::cout << "entity decorator" << std::endl;
}

void EntityDecorator::update() {
    entity->update();
}


sf::Sprite EntityDecorator::getSprite() {
    return entity->getSprite();
}

EntityDecorator::~EntityDecorator() {
    delete(entity);
}
