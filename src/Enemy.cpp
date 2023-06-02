#include <cmath>
#include "Enemy.h"
#include "GameData.h"


Enemy::Enemy(const sf::Texture &_texture, Vector2<float> _startPosition, Rect<float> _localBounds) :
PhysicsEntity(_texture, 4.0f, 999.0f, _localBounds) {
    position = _startPosition;
    int cellCount = 2;
    animator = Animator(*sprite, static_cast<int>(_texture.getSize().x) / cellCount, static_cast<int>(_texture.getSize().y), cellCount, 2);
}

Enemy::Enemy(const sf::Texture &_texture, float _startX, float _startY, Rect<float> _localBounds) :
Enemy(_texture, Vector2<float>(_startX, _startY), _localBounds) {}

void Enemy::update(float _delta) {
    animator.animate(*sprite, _delta);

    // cosine-based horizontal movement
    // note: adjusting t and amplitude may not have the expected effect on movement
    // as it's a force xScalar and does not manipulate position directly
    float t = position.y * 0.25f;
    float amplitude = 20.0f;
    float x = std::cos(t) * amplitude;

    rigidbody->addForce(x, 15.0f);
    PhysicsEntity::update(_delta);

    // if the bottom of the screen is reached, flag as destroyed so EntityManager knows to delete it
    if (position.y > VIEWPORT_HEIGHT) {
        destroyed = true;
    }
}

void Enemy::onCollision() {
    PhysicsEntity::onCollision();
    destroyed = true;
}
