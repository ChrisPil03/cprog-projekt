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
        Sprite(x,y,w,h,imagePath), collider(engine::Collider2D::getInstance(x,y,w,h,tag))
    {
        collider->setParent(this);
    }

    Pickup::~Pickup(){
        std::cout << "Remove collider" << std::endl;
        engine::session.removeComponent(collider);
    }
}