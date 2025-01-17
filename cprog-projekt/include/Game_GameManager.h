#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Component.h"
#include "Label.h"

namespace game
{
    class GameManager : public engine::Component
    {
    public:
        static GameManager* getInstance(engine::Label* lbl){ return new GameManager(lbl); }
        static void collectGem();
        int getCollectedGems() const { return collectedGems; }

    private:
        GameManager(engine::Label* lbl);

        inline static int collectedGems;
        inline static engine::Label* gemsCountLabel;
    };
}

#endif