#include "Session.h"
#include "Game_Pickup.h"
#include "Game_Platform.h"
#include "Game_Player.h"
#include "Map.h"
#include <iostream>

int main (int argc, char** argv){

    std::vector<std::vector<int>> tileMap = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,5,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,5,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,0,0,0,3,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,1},
        {1,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,1},
        {3,3,3,3,3,3,3,3,3,3,3,3,9,9,3,3,3,3,9,8,3,3,3,3,3,3,3,3,3,3},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
    };

    game::Pickup* coin = game::Pickup::getInstance(300,512,16,16,"/images/GoldCoin.png","Coin");
    game::Player* bluePlayer = game::Player::getInstance(300,100, "A", "D", "W", "/images/BlueSlimeIdle.png", "/images/BlueSlimeJump.png", "/images/BlueSlimeFall.png");
    game::Player* redPlayer = game::Player::getInstance(500,100, "Left", "Right", "Up", "/images/RedSlimeIdle.png", "/images/RedSlimeJump.png", "/images/RedSlimeFall.png");
    game::Platform* platform = game::Platform::getInstance(250, 500, 64, 64, "/images/bg.jpg", "Ground");
    engine::Map* map = engine::Map::getInstance(tileMap, "/images/TileMap.png",16,65,2, "Ground");

    engine::session.addComponent(map);
    engine::session.addComponent(coin);
    engine::session.addComponent(bluePlayer);
    engine::session.addComponent(redPlayer);
    engine::session.addComponent(platform);
    engine::session.run();

    return 0;
}