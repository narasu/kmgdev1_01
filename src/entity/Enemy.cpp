#include <cmath>
#include "Enemy.h"
#include "../GameData.h"


Enemy::Enemy(const sf::Texture &_texture, Vector2<float> _startPosition, Rect<float> _localBounds, float _yForce) :
        PhysicsEntity(_texture, 3.0f, 0.98f, _localBounds), yForce(_yForce) {
    position = _startPosition;
    startX = _startPosition.x;
    int cellCount = 2;
    animator = Animator(*sprite, static_cast<int>(_texture.getSize().x) / cellCount, static_cast<int>(_texture.getSize().y), cellCount, 2);
}

Enemy::Enemy(const sf::Texture &_texture, float _startX, float _startY, Rect<float> _localBounds, float _yForce) :
Enemy(_texture, Vector2<float>(_startX, _startY), _localBounds, _yForce) {}

void Enemy::update(float _delta) {
    animator.animate(*sprite, _delta);

    // sine-based horizontal movement
    float t = position.y * 0.2f;
    float amplitude = 7.5f;
    float x = std::sin(t) * amplitude;

    // note: i experimented with applying x = std::cos(t) * amplitude as force to the rigidbody
    // which works, but is much less predictable and harder to fine-tune
    position.x = startX + x;


    rigidbody->addForce(.0f, yForce);
    PhysicsEntity::update(_delta);

    // if the bottom of the screen is reached, flag as destroyed so EntityManager knows to delete it
    if (position.y >= VIEWPORT_HEIGHT - 2) {
        outOfBounds = true;
        destroyed = true;
    }
}

void Enemy::onCollision() {
    destroyed = true;
}
bool Enemy::isOutOfBounds() {
    return outOfBounds;
}