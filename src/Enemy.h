#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy();
    ~Enemy() override = default;
    void update(float _delta) override;
    void initializeTexture() override;
    void animate(float _delta);
protected:
    std::string getTexturePath() override;
    std::string texturePath = "assets/sprites/enemy_crustachnid_sheet.png";
private:
    sf::Vector2<int> cellSize;
    float animationDelta = 0.f;
    int currentCell = 0;
    int cellCount = 2;
    int frameRate = 2;
};