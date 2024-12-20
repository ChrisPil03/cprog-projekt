#include "Game_Pickup.h"

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
        // std::cout<< "remove pickup collider"<< std::endl;
        // session.removeComponent(collider);
        // Why does it not work to remove collider here?
    }
}