#include "Animator.h"

Animator::Animator() : cellCount(1), frameRate(2) {

}

Animator::Animator(sf::Sprite& _sprite, int _cellWidth, int _cellHeight, int _cellCount, int _frameRate) : cellCount(_cellCount), frameRate(_frameRate) {
    cellSize = sf::Vector2i(_cellWidth, _cellHeight);
    sf::IntRect r(cellSize.x * currentCell, 0, cellSize.x, cellSize.y);
    _sprite.setTextureRect(r);
}

void Animator::animate(sf::Sprite& _sprite, float _delta) {

    animationDelta += _delta;
    float rate = 1.f/ float(frameRate);
    if (animationDelta < rate) {
        return;
    }

    currentCell < cellCount - 1 ? currentCell += 1 : currentCell = 0;

    sf::IntRect r(cellSize.x * currentCell, 0, cellSize.x, cellSize.y);
    _sprite.setTextureRect(r);
    animationDelta = 0.f;
}
