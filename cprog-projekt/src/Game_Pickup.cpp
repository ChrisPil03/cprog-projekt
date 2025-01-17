#include "Game_Pickup.h"
#include "Session.h"
#include "Component.h"
#include <iostream>

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
        // set parent too nullptr becasue collider is a child and will be removed next frame
        // if parent is not set to nullptr there will be one frame where parent is pointing to something unknown
        collider->setParent(nullptr);
        engine::session.removeComponent(collider);
    }
}