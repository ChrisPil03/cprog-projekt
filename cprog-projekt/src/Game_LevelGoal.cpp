#include "Game_LevelGoal.h"
#include "Session.h"
#include "Collider2D.h"
#include "Game_Player.h"
#include <iostream>

namespace game
{
    LevelGoal* LevelGoal::getInstance(int x, int y, std::string color){
        return new LevelGoal(x,y,color);
    }

    LevelGoal::LevelGoal(int x, int y, std::string color) :
        Sprite(x,y,GOAL_WIDTH,GOAL_HEIGHT, (color == "Blue") ? BLUE_GOAL : RED_GOAL),
        color(color), collider(engine::Collider2D::getInstance(x,y,GOAL_WIDTH,GOAL_HEIGHT,GOAL_TAG))
    {
        collider->setParent(this);
        bluePlayerAtGoal = false;
        redPlayerAtGoal = false;
    }

    void LevelGoal::update(){
        checkLevelComplete();
    }

    void LevelGoal::checkLevelComplete(){
        if (engine::Collider2D* other = collider->hasCollided("Player")){
            if (Player* player = dynamic_cast<Player*>(other->getParent())){
                if (this->getColor() == player->getColor()){
                    if (color == "Blue"){
                        bluePlayerAtGoal = true;
                    }else{
                        redPlayerAtGoal = true;
                    }
                    if(bluePlayerAtGoal && redPlayerAtGoal){
                        completeLevel();
                    }
                }
            }
        }else{
            if (bluePlayerAtGoal){
                bluePlayerAtGoal = false;
            }
            else if (redPlayerAtGoal){
                redPlayerAtGoal = false;
            }
        }
    }

    void LevelGoal::completeLevel(){
        std::cout << "Goal" << std::endl;
    }

    LevelGoal::~LevelGoal(){
        engine::session.removeComponent(collider);
    }
}