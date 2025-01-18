#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Component.h"
#include "Game_GameManager.h"
#include "Game_Player.h"
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
        Player* bluePlayer;
        Player* redPlayer;
        GameManager* gameManager;
    };
}

#endif