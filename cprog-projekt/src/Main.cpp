#include "Session.h"
#include "Game_Pickup.h"
#include "Game_Platform.h"
#include "Game_Player.h"
#include "Map.h"
#include <iostream>

int main (int argc, char** argv){

    std::vector<std::vector<int>> tileMap = {
        {27,35,0,0,0,0,0,0,0,36,21,21,21,21,21,21,21,21,35,0,0,0,0,0,36,21,21,21,21,26},
        {12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10},
        {12,0,0,5,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10},
        {19,0,0,5,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10},
        {17,3,3,3,3,3,3,3,3,3,50,0,0,0,49,3,3,3,3,3,31,0,0,0,0,0,0,0,0,15},
        {12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36,21,40,3,3,3,50,0,0,0,49,14},
        {12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10},
        {12,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10},
        {12,0,-1,0,51,5,5,5,5,5,5,5,5,7,3,31,0,0,0,0,0,0,0,0,0,0,0,0,0,15},
        {12,0,-1,0,0,0,0,0,0,0,0,0,0,43,45,32,7,3,3,3,6,5,5,5,5,5,5,7,3,14},
        {12,0,-1,0,0,0,0,0,0,0,0,0,0,0,10,18,2,2,11,0,0,0,0,0,43,44,45,2,2,16},
        {24,0,0,0,0,0,0,0,0,0,0,0,0,0,36,21,21,21,35,0,0,0,0,0,0,0,36,21,21,26},
        {25,5,5,5,5,5,5,5,5,5,5,41,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10},
        {12,0,0,0,0,0,0,0,0,0,36,60,5,5,57,0,56,5,5,5,5,7,3,50,0,0,0,0,0,10},
        {24,0,0,0,0,0,0,0,0,0,0,0,0,43,44,44,44,48,0,0,0,0,0,0,0,0,0,0,0,15},
        {25,5,5,5,5,52,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,3,3,14},
        {12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,54,2,2,16},
        {24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,42,5,5,23,1,1,1},
        {25,5,5,5,5,5,5,5,5,5,41,0,0,42,5,5,5,41,0,0,42,5,5,34,2,2,16,1,1,1},
        {18,2,2,2,2,2,2,2,2,2,32,5,5,34,2,2,2,32,5,5,34,2,2,16,1,1,1,1,1,1}
    };

    engine::Sprite* background = engine::Sprite::getInstance(0,0,960,640,"/images/BG.png");
    engine::Sprite* clouds = engine::Sprite::getInstance(0,0,960,640,"/images/clouds.png");
    engine::Map* map = engine::Map::getInstance(tileMap, "/images/TileMap.png",16,65,2, "Ground");
    game::Platform* platform1 = game::Platform::getInstance(32, 256, 96, 16, "/images/bg.jpg", "Ground",false,1,112);
    game::Platform* platform2 = game::Platform::getInstance(800, 160, 96, 16, "/images/bg.jpg", "Ground",false,1,112);
    game::Pickup* coin = game::Pickup::getInstance(300,512,16,16,"/images/GoldCoin.png","Coin");

    engine::session.addComponent(background);
    engine::session.addComponent(clouds);
    engine::session.addComponent(map);
    engine::session.addComponent(platform1);
    engine::session.addComponent(platform2);
    engine::session.addComponent(coin);

    game::Player* bluePlayer = game::Player::getInstance(64,400, "A", "D", "W", "/images/BlueSlimeIdle.png", "/images/BlueSlimeJump.png", "/images/BlueSlimeFall.png");
    game::Player* redPlayer = game::Player::getInstance(64,480, "Left", "Right", "Up", "/images/RedSlimeIdle.png", "/images/RedSlimeJump.png", "/images/RedSlimeFall.png");

    engine::session.addComponent(bluePlayer);
    engine::session.addComponent(redPlayer);
    
    engine::session.run();

    return 0;
}