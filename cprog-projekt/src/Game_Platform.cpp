#include "Game_Platform.h"

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
    }

    void Platform::update(){  
        if (horizontalMovement){
            getRect()->x += speed;
        }else{
            getRect()->y += speed;
        }    

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