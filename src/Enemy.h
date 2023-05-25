#include "Entity.h"
#include "Animator.h"

class Enemy : public Entity {
public:
    explicit Enemy(sf::Texture* _texture);
    void update(float _delta) override;
protected:
private:
    Animator animator;
};