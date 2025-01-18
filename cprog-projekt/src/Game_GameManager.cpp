#include "Game_GameManager.h"
#include <string>

namespace game
{
    GameManager* GameManager::getInstance(){
        if (!gameManager){
            return new GameManager();
        }
        return nullptr;
    }

    GameManager::GameManager() : collectedGems(0), gemsCountLabel(nullptr){
        if (!gameManager){
            gameManager = this;
        }
    }

    void GameManager::collectGem(){
        collectedGems++;
        if(gemsCountLabel){
            gemsCountLabel->setText(std::to_string(collectedGems));
        }
    }

    // Only call this function when label has been deleted
    // Otherwise memory leak
    void GameManager::resetGems(){
        collectedGems = 0;
        gemsCountLabel = nullptr;
    }
}