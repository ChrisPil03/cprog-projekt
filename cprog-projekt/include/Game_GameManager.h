#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Component.h"

namespace game
{
    class GameManager : public engine::Component
    {
    public:
        static GameManager* getInstance(){ return new GameManager(); }
        void collectGem(){ collectedGems++; }
        const int& getCollectedGems(){ return collectedGems; }
        void update();
    private:
        GameManager() : collectedGems(0){}

        int collectedGems;
    };
}

#endif