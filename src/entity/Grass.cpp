#include "Grass.h"
#include "../GameData.h"

Grass::Grass(const sf::Texture &_texture, Vector2<float> _startPosition, float _speedY) : BaseEntity(_texture){
    position = _startPosition;
    speedY = _speedY;
}

Grass::Grass(const sf::Texture &_texture, float _posX, float _posY, float _speedY) :
Grass(_texture, Vector2<float>(_posX,_posY), _speedY) {}

void Grass::update(float _delta) {
    position.y += speedY * _delta;

    if (position.y > VIEWPORT_HEIGHT) {
        destroyed = true;
    }

    // round to whole numbers to prevent sub-pixel rendering
    // does this make everything jittery and also slightly inaccurate? yes
    // but it really sells the arcade aesthetic, so it's here to stay
    sprite->setPosition(roundf(position.x), roundf(position.y));
}