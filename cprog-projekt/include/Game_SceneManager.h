#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Component.h"
#include <vector>

namespace game
{
    class SceneManager
    {
    public:
        static SceneManager* getInstance(){ return new SceneManager();}
        void loadMainMenu();
        void loadLevel_1();
        ~SceneManager() { clearScene(); }
    private:
        SceneManager();
        void clearScene();
        std::vector<engine::Component*> mainMenu;
        std::vector<engine::Component*> level_1;
        engine::Component* bluePlayer;
        engine::Component* redPlayer;
        engine::Component* gameManager;
    };
}

#endif