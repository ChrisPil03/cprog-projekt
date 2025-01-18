#include "Game_SceneManager.h"
#include "Game_GameManager.h"
#include "Game_Box.h"
#include "Game_Button.h"
#include "Game_Pickup.h"
#include "Game_Platform.h"
#include "Game_LevelGoal.h"
#include "Map.h"
#include "Label.h"
#include "MemButton.h"
#include "Session.h"
#include "SoundManager.h"
//#include <iostream>

namespace game
{
    SceneManager::SceneManager(){
        if (!sceneManager){
            sceneManager = this;

            loadMainMenu();

            blueMenuSlime = nullptr;
            bluePlayer = nullptr;
            blueWater = nullptr;
            redMenuSlime = nullptr;
            redPlayer = nullptr;
            redWater = nullptr;
        }
    }

    void SceneManager::loadLevelComplete(){
        // std::cout << "Loading level complete UI" << std::endl;

        // Buttons
        levelComplete.push_back(engine::MemButton<SceneManager>::getInstance(550,230,180,180,"/images/Button_Replay.png",sceneManager,&SceneManager::loadLevel_1));
        levelComplete.push_back(engine::MemButton<SceneManager>::getInstance(230,230,180,180,"/images/Button_ExitArrow.png",sceneManager,&SceneManager::loadMainMenu));

        // Add level complete UI too session
        for (engine::Component* c : levelComplete){
            engine::session.addComponent(c);
        }
    }

    void SceneManager::loadMainMenu(){
        // std::cout << "Loading main menu" << std::endl;

        clearScene();

        //Play menu music
        engine::SoundManager::soundManager->playSound("MenuMusic", true);

        // Background
        mainMenu.push_back(engine::Sprite::getInstance(0,0,960,640,"/images/BG.png"));
        mainMenu.push_back(engine::Sprite::getInstance(0,0,960,640,"/images/clouds.png"));
        mainMenu.push_back(engine::Sprite::getInstance(0,0,960,640,"/images/Title.png"));

        // Buttons
        mainMenu.push_back(engine::MemButton<SceneManager>::getInstance(390,230,180,180,"/images/Button_Play.png",sceneManager,&SceneManager::loadLevel_1));

        // Add main menu components too session
        for (engine::Component* c : mainMenu){
            engine::session.addComponent(c);
        }

        blueMenuSlime = engine::AnimatedSprite::getInstance(650,350,240,240,engine::Animation::getInstance("Idle","/images/BlueSlimeIdle.png", 32, 32, 6, 10, true));
        blueMenuSlime->flipX();
        redMenuSlime = engine::AnimatedSprite::getInstance(70,350,240,240,engine::Animation::getInstance("Idle","/images/RedSlimeIdle.png", 32, 32, 6, 10, true));

        engine::session.addComponent(blueMenuSlime);
        engine::session.addComponent(redMenuSlime);
    }

    void SceneManager::loadLevel_1(){
        // std::cout << "Loading level 1" << std::endl;

        clearScene();

        // Play level music
        engine::SoundManager::soundManager->playSound("LevelMusic", true);

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

        // box
        level_1.push_back(Box::getInstance(574,384,30,31));

        // platforms and buttons controlling platforms
        Platform* platform1 = Platform::getInstance(32, 256, 96, 16, "/images/Platform.png", "Ground", false, 1, 78);
        Platform* platform2 = Platform::getInstance(832, 160, 96, 16, "/images/Platform.png", "Ground", false, 1, 78);
        Platform* platform3 = Platform::getInstance(320, 128, 96, 16, "/images/Platform.png", "Ground", true, 1, 192);
        level_1.push_back(platform1);
        level_1.push_back(platform2);
        level_1.push_back(platform3);
        level_1.push_back(game::Button::getInstance(320,368, 16, 16, platform1));
        level_1.push_back(game::Button::getInstance(192,240, 16, 16, platform1));
        level_1.push_back(game::Button::getInstance(580,272, 16, 16, platform2));
        level_1.push_back(game::Button::getInstance(768,144, 16, 16, platform2));
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

        // UI
        engine::Label* gemLabel = engine::Label::getInstance(864, 32, 28, 32, "0");
        level_1.push_back(gemLabel);
        level_1.push_back(engine::Sprite::getInstance(900,36,18,22,"/images/Gem.png"));

        GameManager::gameManager->setGemLabel(gemLabel);

        // Add all components to session
        for (engine::Component* c : level_1){
            engine::session.addComponent(c);
        }

        // The following needs to be done after adding everything to session. If not they will be rendered behind everything else
        // players
        bluePlayer = Player::getInstance(64,400, "A", "D", "W", "Blue");
        redPlayer = Player::getInstance(64,480, "Left", "Right", "Up", "Red");

        // water
        blueWater = Water::getInstance(352,586,64,24,"Red");
        redWater = Water::getInstance(576,586,64,24,"Blue");

        // Add players and water to session
        engine::session.addComponent(bluePlayer);
        engine::session.addComponent(redPlayer);
        engine::session.addComponent(blueWater);
        engine::session.addComponent(redWater);
    }

    // Is called when something is deleted during playtime istead of session.removeComponent
    // Used in Game_Player.cpp onCollision()
    void SceneManager::removeComponent(engine::Component* comp){
        removeComponentFromVector(comp,level_1);
    }

    void SceneManager::removeComponentFromVector(engine::Component* comp,std::vector<engine::Component*>& vec){
        for (std::vector<engine::Component*>::iterator iter = vec.begin(); iter != vec.end(); iter++){
            if (*iter == comp){
                engine::session.removeComponent(comp);
                vec.erase(iter);
                return;
            }
        }
    }

    void SceneManager::clearScene(){
        if (mainMenu.size() != 0){
            for (engine::Component* c : mainMenu){
                engine::session.removeComponent(c);
            }
            mainMenu.clear();
            engine::session.removeComponent(blueMenuSlime);
            engine::session.removeComponent(redMenuSlime);
            blueMenuSlime = nullptr;
            redMenuSlime = nullptr;
        }
        if (level_1.size() != 0){
            for (engine::Component* c : level_1){
                engine::session.removeComponent(c);
            }
            level_1.clear();
            engine::session.removeComponent(bluePlayer);
            engine::session.removeComponent(redPlayer);
            engine::session.removeComponent(blueWater);
            engine::session.removeComponent(redWater);
            bluePlayer = nullptr;
            redPlayer = nullptr;
            blueWater = nullptr;
            redPlayer = nullptr;
            GameManager::gameManager->resetGems();
        }
        if(levelComplete.size() != 0){
            for (engine::Component* c : levelComplete){
                engine::session.removeComponent(c);
            }
            levelComplete.clear();
        }
    }
}