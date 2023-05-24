#include <SFML/Graphics.hpp>

class Animator {
public:
    Animator(sf::Sprite& _sprite, int _cellWidth, int _cellHeight, int _cellCount = 1, int _frameRate = 2);
    void animate(sf::Sprite& _sprite, float _delta);
private:
    sf::Vector2<int> cellSize;
    float animationDelta = 0.f;
    int currentCell = 0;
    int cellCount;
    int frameRate;
};