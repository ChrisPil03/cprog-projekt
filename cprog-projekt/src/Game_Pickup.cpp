#include "Game_Pickup.h"
#include "Session.h"

namespace game
{
    Pickup* Pickup::getInstance(int x, int y, int w, int h, std::string imagePath, std::string tag){
        return new Pickup(x,y,w,h,imagePath,tag);
    }

    Pickup::Pickup(int x, int y, int w, int h, std::string imagePath, std::string tag) :
        Sprite(x,y,w,h,imagePath), collider(engine::Collider2D::getInstance(x,y,w,h,tag)),
        moveAnimSpeed(7), changeDirectionSpeed(moveAnimSpeed*6), speed(1), counter(0)
    {
        collider->setParent(this);
    }

    void Pickup::update(){
        playMoveAnim();
    }

    void Pickup::playMoveAnim(){
        counter++;
        if (counter % moveAnimSpeed == 0){
            getRect()->y += speed;
        }
        if (counter % changeDirectionSpeed == 0){
            speed *= -1;
            counter = 0;
        }
    }

    Pickup::~Pickup(){
        engine::session.removeComponent(collider);
    }
}