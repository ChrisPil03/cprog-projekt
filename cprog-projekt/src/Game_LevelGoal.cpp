#include "Game_LevelGoal.h"
#include "Session.h"
#include "Collider2D.h"
#include "Game_Player.h"
#include "Game_SceneManager.h"

namespace game
{
    LevelGoal* LevelGoal::getInstance(int x, int y, std::string color){
        return new LevelGoal(x,y,color);
    }

    LevelGoal::LevelGoal(int x, int y, std::string color) :
        Sprite(x,y,GOAL_WIDTH,GOAL_HEIGHT, (color == "Blue") ? BLUE_GOAL_CLOSED : RED_GOAL_CLOSED),
        color(color), collider(engine::Collider2D::getInstance(x,y,GOAL_WIDTH,GOAL_HEIGHT,GOAL_TAG))
    {
        levelComplete = false;
        collider->setParent(this);
        bluePlayerAtGoal = false;
        redPlayerAtGoal = false;
    }

    void LevelGoal::update(){
        checkLevelComplete();

        // Shortcut for instant levelComplete
        if (!levelComplete && color == "Blue" && engine::session.keyDown("V")){
            completeLevel();
        }
    }

    void LevelGoal::checkLevelComplete(){
        if (engine::Collider2D* other = collider->hasCollided("Player")){
            if (Player* player = dynamic_cast<Player*>(other->getParent())){
                if (this->getColor() == player->getColor()){
                    if (color == "Blue"){
                        bluePlayerAtGoal = true;
                        changeTexture(BLUE_GOAL_OPEN);
                    }else{
                        redPlayerAtGoal = true;
                        changeTexture(RED_GOAL_OPEN);
                    }
                    if(bluePlayerAtGoal && redPlayerAtGoal && !levelComplete && color == "Blue"){
                        completeLevel();
                    }
                }
            }
        }else{
            if (bluePlayerAtGoal && color == "Blue"){
                bluePlayerAtGoal = false;
                if(!levelComplete){
                    changeTexture(BLUE_GOAL_CLOSED);
                }
            }
            if (redPlayerAtGoal && color == "Red"){
                redPlayerAtGoal = false;
                if(!levelComplete){
                    changeTexture(RED_GOAL_CLOSED);
                }
            }
        }
    }

    void LevelGoal::completeLevel(){
        levelComplete = true;
        SceneManager::sceneManager->loadLevelComplete();
    }

    LevelGoal::~LevelGoal(){
        engine::session.removeComponent(collider);
    }
}