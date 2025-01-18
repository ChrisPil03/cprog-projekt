#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Component.h"
#include "Game_GameManager.h"
#include "Game_Player.h"
#include "Game_Water.h"
#include <vector>

namespace game
{
    class SceneManager
    {
    public:
        static SceneManager* getInstance(){ return new SceneManager();}
        void loadMainMenu();
        void loadLevel_1();
        void loadLevelComplete();
        void removeComponent(engine::Component*);
        ~SceneManager() { clearScene(); }

        inline static SceneManager* sceneManager = nullptr;
    private:
        SceneManager();
        void clearScene();
        void removeComponentFromVector(engine::Component*,std::vector<engine::Component*>&);
        
        std::vector<engine::Component*> mainMenu, level_1, levelComplete;

        // Needed because layer order has not been implemented
        // Objects with animations has to be added seperatly to reder them infront of everything else
        Player* bluePlayer;
        Player* redPlayer;
        Water* blueWater;
        Water* redWater;

    };
}

#endif