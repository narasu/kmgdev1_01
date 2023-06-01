#include "Managers.h"

void CollisionManager::update(const std::list<std::shared_ptr<Entity>>& _entityList) {
    bounds.clear();
    /*for (auto& it : _entityList) {
        if (std::dynamic_pointer_cast<PhysicsEntity>(it)) {
            bounds.push_back(it->getBoundsGlobal());
        }

    }*/

}

void CollisionManager::sortBounds() {

    /*for(int i=0;i<10;i++)
    {
        cout <<myarray[i]<<"\t";
    }
    for(int k=1; k<10; k++)
    {
        int temp = myarray[k];
        int j= k-1;
        while(j>=0 && temp <= myarray[j])
        {
            myarray[j+1] = myarray[j];
            j = j-1;
        }
        myarray[j+1] = temp;
    }
    cout<<"\nSorted list is \n";
    for(int i=0;i<10;i++)
    {
        cout <<myarray[i]<<"\t";
    }*/
}
