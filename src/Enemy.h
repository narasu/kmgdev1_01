#include "Entity.h"
#include "Animator.h"

class Enemy : public Entity {
public:
    Enemy();
    ~Enemy() override;
    void update(float _delta) override;
    void initializeTexture() override;
protected:
    std::string getTexturePath() override;
    std::string texturePath = "assets/sprites/enemy_crustachnid_sheet.png";
private:
    Animator* animator;
};