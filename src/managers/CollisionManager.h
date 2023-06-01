#include "Managers.h"
class CollisionManager {
public:
    void update(const std::list<std::shared_ptr<Entity>>& _entityList);
    void sortBounds();
private:
    std::vector<Rect<float>> bounds;
};