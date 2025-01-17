#include "Game_GameManager.h"
#include <string>
#include <iostream>

namespace game
{
    GameManager::GameManager(engine::Label* lbl){
        collectedGems = 0;
        gemsCountLabel = lbl;
    }

    void GameManager::collectGem(){
        collectedGems++;
        gemsCountLabel->setText(std::to_string(collectedGems));
    }
}