#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Component.h"
#include "Label.h"

namespace game
{
    class GameManager
    {
    public:
        static GameManager* getInstance();
        void collectGem();
        int getCollectedGems() const { return collectedGems; }
        void resetGems();
        void setGemLabel(engine::Label* lbl) { gemsCountLabel = lbl; }
        ~GameManager(){}

        inline static GameManager* gameManager = nullptr;
    private:
        GameManager();

        int collectedGems;
        engine::Label* gemsCountLabel;
    };
}

#endif