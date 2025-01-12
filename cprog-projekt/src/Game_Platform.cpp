#include "Game_Platform.h"
#include "Component.h"

namespace game
{
    Platform* Platform::getInstance(int x, int y, int w, int h, std::string imagePath, std::string tag, bool horizontal, int colPos1, int colPos2){
        return new Platform(x,y,w,h,imagePath,tag,horizontal,colPos1,colPos2);
    }

    Platform::Platform(int x, int y, int w, int h, std::string imagePath, std::string tag, bool horizontal, int colPos1, int colPos2) : 
        Sprite(x,y,w,h,imagePath), collider(engine::Collider2D::getInstance(x,y,w,h,tag)), horizontalMovement(horizontal)
    {
        if (horizontal){
            target1 = engine::Collider2D::getInstance(x-colPos1,y,1, 1, "Target");
            target2 = engine::Collider2D::getInstance(x+w+colPos1,y,1, 1, "Target");
        }else{
            target1 = engine::Collider2D::getInstance(x,y-colPos1,1, 1, "Target");
            target2 = engine::Collider2D::getInstance(x,y+h+colPos2,1, 1, "Target");
        }
        collider->setParent(this);
        collider->setJumpThrought(true);
    }

    void Platform::update(){  
        if (horizontalMovement){
            getRect()->x += speedX;
        }else{
            if(canMove){
                getRect()->y += speedY;
            }         
        }    

        if(collider->hasCollided("Target")){
            hasCollidedWTarget = true;
            speedX *= -1;
            speedY *= -1;
        } else{
            hasCollidedWTarget = false;
        }
    }

    void Platform::setSpeed(int newSpeedX, int newSpeedY) {
        speedX = newSpeedX;
        speedY = newSpeedY;
    }


    Platform::~Platform(){
        engine::session.removeComponent(collider);
        engine::session.removeComponent(target1);
        engine::session.removeComponent(target2);
    }
}