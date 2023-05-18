#include "AnimationDecorator.h"
#include <iostream>
#pragma once
AnimationDecorator::AnimationDecorator(IEntity *_entity) : EntityDecorator(_entity) {
    std::cout << "animation decorator" << std::endl;

}

void AnimationDecorator::update() {
    EntityDecorator::update();
}
