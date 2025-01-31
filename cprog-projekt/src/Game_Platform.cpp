#include "Game_Platform.h"

namespace game
{
    Platform* Platform::getInstance(int x, int y, int w, int h, std::string imagePath, std::string tag, bool horizontal, int colPos1, int colPos2){
        return new Platform(x,y,w,h,imagePath,tag,horizontal,colPos1,colPos2);
    }

    Platform::Platform(int x, int y, int w, int h, std::string imagePath, std::string tag, bool horizontal, int colPos1, int colPos2) : 
        Sprite(x,y,w,h,imagePath), collider(engine::Collider2D::getInstance(x,y,w,h,tag)), horizontalMovement(horizontal), isControlled(false)
    {
        if (horizontal){
            target1 = engine::Collider2D::getInstance(x-colPos1,y,1, 1, "Target");
            target2 = engine::Collider2D::getInstance(x+w+colPos2,y,1, 1, "Target");
        }else{
            target1 = engine::Collider2D::getInstance(x,y-colPos1,1, 1, "Target");
            target2 = engine::Collider2D::getInstance(x,y+h+colPos2,1, 1, "Target");
        }
        collider->setParent(this);
    }

    void Platform::update(){  
        move();

        if(isControlled){
            moveUp();
        }

        if(collider->hasCollided("Target") && !isControlled){
            changeDirection();
        }
    }

    void Platform::move(){
        if (horizontalMovement){
            if ((speedX > 0 && getRect()->x + getRect()->w <= target2->getColliderRect()->x) ||
                (speedX < 0 && getRect()->x >= target1->getColliderRect()->x))
            {
                getRect()->x += speedX;
            }
        }else{
            if ((speedY < 0 && getRect()->y >= target1->getColliderRect()->y) ||
                (speedY > 0 && getRect()->y + getRect()->h <= target2->getColliderRect()->y))
            {
                getRect()->y += speedY;
            }
        }  
    }

    void Platform::moveUp(){
        if(speedY > 0){
            speedY *= -1;
        }
    }

    void Platform::changeDirection(){
        if(horizontalMovement){
            speedX *= -1;
        }else{
            speedY *= -1;
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