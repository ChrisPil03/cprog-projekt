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
        void changeSceneTo(std::string);
    private:
        SceneManager();
        void loadMainMenu();
        void loadLevel_1();
        std::vector<engine::Component*> mainMenu;
        std::vector<engine::Component*> level_1;
        engine::Component* bluePlayer;
        engine::Component* redPlayer;
    };
}

#endif