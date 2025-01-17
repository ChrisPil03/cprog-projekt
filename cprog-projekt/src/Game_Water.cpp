#include "Game_Water.h"
#include "Session.h"

namespace game
{
    Water* Water::getInstance(int x, int y, int w, int h, std::string color){
        return new Water(x,y,w,h,color);
    }

    Water::Water(int x, int y, int w, int h, std::string color) :
        Sprite(x,y,w,h, (color == "Blue") ? BLUE_WATER : RED_WATER),
        color(color),
        collider(engine::Collider2D::getInstance(x,y,w,h,TAG))
    {
        collider->setParent(this);
    }

    Water::~Water(){
        engine::session.removeComponent(collider);
    }
}