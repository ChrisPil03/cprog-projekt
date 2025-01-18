#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Component.h"
#include "Label.h"

namespace game
{
    class GameManager
    {
    public:
        static GameManager* getInstance(engine::Label* lbl){ return new GameManager(lbl); }
        static void collectGem();
        static int getCollectedGems() { return collectedGems; }
        ~GameManager(){}

    private:
        GameManager(engine::Label* lbl);

        inline static int collectedGems;
        inline static engine::Label* gemsCountLabel;
    };
}

#endif