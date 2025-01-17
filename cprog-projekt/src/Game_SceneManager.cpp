#include "Game_SceneManager.h"
#include "Game_Box.h"
#include "Game_Button.h"
#include "Game_Pickup.h"
#include "Game_Platform.h"
#include "Game_Player.h"
#include "Game_LevelGoal.h"
#include "Game_Water.h"
#include "Map.h"
#include "Session.h"

namespace game
{
    SceneManager::SceneManager(){
        loadLevel_1();
    }

    void SceneManager::loadMainMenu(){
        clearScene();

        // background
        mainMenu.push_back(engine::Sprite::getInstance(0,0,960,640,"/images/BG.png"));
        mainMenu.push_back(engine::Sprite::getInstance(0,0,960,640,"/images/clouds.png"));

        // Add main menu components to session
        for (engine::Component* c : mainMenu){
            engine::session.addComponent(c);
        }
    }

    void SceneManager::loadLevel_1(){
        clearScene();

        // level 1 map
        std::vector<std::vector<int>> tileMap = {
            {27,35, 0, 0, 0, 0, 0, 0, 0,36,21,21,21,21,21,21,21,21,35, 0, 0, 0, 0, 0,36,21,21,21,21,26},
            {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10},
            {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10},
            {19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10},
            {17, 3, 3, 3, 3, 3, 3, 3, 3,50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 3,31, 0, 0, 0, 0, 0, 0, 0,10},
            {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,36,21,63, 3, 3, 3,50, 0, 0, 0,10},
            {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10},
            {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10},
            {12, 0, 0, 0,51, 5, 5, 5, 5, 5, 5, 5, 5, 7, 3,31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15},
            {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,45,32, 7, 3, 3, 3, 6, 5, 5, 5, 5, 5, 5, 7, 3,14},
            {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10,18, 2, 2,11, 0, 0, 0, 0, 0,43,44,45, 2, 2,16},
            {24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,36,21,21,21,35, 0, 0, 0, 0, 0, 0, 0,36,21,21,26},
            {25, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,10},
            {12, 0, 0, 0, 0, 0, 0, 0, 0, 0,36,60, 5, 5,57, 0,56, 5, 5, 5, 5, 7, 3,50, 0, 0, 0, 0, 0,10},
            {24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,43,44,44,44,48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15},
            {25, 5, 5, 5, 5,52, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 3, 3,14},
            {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,54, 2, 2,16},
            {24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,42, 5,23, 1, 1, 1},
            {25, 5, 5, 5, 5, 5, 5, 5, 5, 5,41, 0, 0,42, 5, 5, 5,41, 0, 0,42, 5, 5, 5,34, 2,16, 1, 1, 1},
            {18, 2, 2, 2, 2, 2, 2, 2, 2, 2,32, 5, 5,34, 2, 2, 2,32, 5, 5,34, 2, 2, 2,16, 1, 1, 1, 1, 1}
        };

        // background
        level_1.push_back(engine::Sprite::getInstance(0,0,960,640,"/images/BG.png"));
        level_1.push_back(engine::Sprite::getInstance(0,0,960,640,"/images/clouds.png"));

        // goal
        level_1.push_back(LevelGoal::getInstance(96,64,"Red"));
        level_1.push_back(LevelGoal::getInstance(200,64,"Blue"));

        // water
        level_1.push_back(Water::getInstance(352,586,64,24,"Red"));
        level_1.push_back(Water::getInstance(576,586,64,24,"Blue"));

        // box
        level_1.push_back(Box::getInstance(574,384,30,31));

        // platforms and buttons controlling platforms
        Platform* platform1 = Platform::getInstance(32, 256, 96, 16, "/images/bg.jpg", "Ground", false, 1, 78);
        Platform* platform2 = Platform::getInstance(832, 160, 96, 16, "/images/bg.jpg", "Ground", false, 1, 78);
        Platform* platform3 = Platform::getInstance(320, 128, 96, 16, "/images/bg.jpg", "Ground", true, 1, 192);
        level_1.push_back(platform1);
        level_1.push_back(platform2);
        level_1.push_back(platform3);
        level_1.push_back(game::Button::getInstance(320,368, 16, 16, "/images/Box.png", platform1));
        level_1.push_back(game::Button::getInstance(192,240, 16, 16, "/images/Box.png", platform1));
        level_1.push_back(game::Button::getInstance(580,272, 16, 16, "/images/Box.png", platform2));
        level_1.push_back(game::Button::getInstance(768,144, 16, 16, "/images/Box.png", platform2));
        platform3->setSpeedX(1);

        // map
        level_1.push_back(engine::Map::getInstance(tileMap, "/images/TileMap.png",16,65,2, "Ground"));

        // pickups
        level_1.push_back(Pickup::getInstance(488,534,18,22,"/images/Gem.png","Gem"));
        level_1.push_back(Pickup::getInstance(696,534,18,22,"/images/Gem.png","Gem"));
        level_1.push_back(Pickup::getInstance(872,438,18,22,"/images/Gem.png","Gem"));
        level_1.push_back(Pickup::getInstance(680,375,18,22,"/images/Gem.png","Gem"));
        level_1.push_back(Pickup::getInstance(160,343,18,22,"/images/Gem.png","Gem"));
        level_1.push_back(Pickup::getInstance(240,343,18,22,"/images/Gem.png","Gem"));
        level_1.push_back(Pickup::getInstance(300,215,18,22,"/images/Gem.png","Gem"));
        level_1.push_back(Pickup::getInstance(380,215,18,22,"/images/Gem.png","Gem"));
        level_1.push_back(Pickup::getInstance(736,248,18,22,"/images/Gem.png","Gem"));
        level_1.push_back(Pickup::getInstance(355,90,18,22,"/images/Gem.png","Gem"));
        level_1.push_back(Pickup::getInstance(455,90,18,22,"/images/Gem.png","Gem"));
        level_1.push_back(Pickup::getInstance(555,90,18,22,"/images/Gem.png","Gem"));

        // Add all components to session
        for (engine::Component* c : level_1){
            engine::session.addComponent(c);
        }

        // The following needs to be done after adding everything to session. If not the players will be rendered behind everything else
        // players
        bluePlayer = Player::getInstance(64,400, "A", "D", "W", "Blue");
        redPlayer = Player::getInstance(64,480, "Left", "Right", "Up", "Red");

        // Add players to session
        engine::session.addComponent(bluePlayer);
        engine::session.addComponent(redPlayer);
    }

    void SceneManager::clearScene(){
        if (mainMenu.size() != 0){
            for (engine::Component* c : mainMenu){
                engine::session.removeComponent(c);
            }
        }
        if (level_1.size() != 0){
            for (engine::Component* c : level_1){
                engine::session.removeComponent(c);
            }
            engine::session.removeComponent(bluePlayer);
            engine::session.removeComponent(redPlayer);
        }
    }
}