#include "Game_Platform.h"

namespace game
{
    Platform* Platform::getInstance(int x, int y, int w, int h, std::string imagePath, std::string tag){
        return new Platform(x,y,w,h,imagePath,tag);
    }

    Platform::Platform(int x, int y, int w, int h, std::string imagePath, std::string tag) : 
        Sprite(x,y,w,h,imagePath), collider(engine::Collider2D::getInstance(x,y,w,h,tag)),
        target1(engine::Collider2D::getInstance(x+60+w,y,1, 10, "Target")),
        target2(engine::Collider2D::getInstance(x-60,y,1, 10, "Target"))
    {
        collider->setParent(this);
    }

    void Platform::update(){      
        getRect()->x += speed;

        if(collider->hasCollided("Target")){
            speed *= -1;
        }
    }

    Platform::~Platform(){
        engine::session.removeComponent(collider);
        engine::session.removeComponent(target1);
        engine::session.removeComponent(target2);
    }
}