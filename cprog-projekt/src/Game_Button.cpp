#include "Game_Button.h"

namespace game {

    Button* Button::getInstance(int x, int y, int w, int h, std::string imagePath, Platform* platform) {
        return new Button(x, y, w, h, imagePath, platform);
    }

    Button::Button(int x, int y, int w, int h, std::string imagePath, Platform* platform) : engine::Sprite(x, y, w, h, imagePath), platform(platform)  {
        collider = engine::Collider2D::getInstance(x, y, w, h, "Button");
        collider->setParent(this);
        platform->setIsControlled(true);
    }

    void Button::update(){
        if(collider->hasCollided("Player")){
            platform->setSpeed(0,1);
        } else {
            platform->setSpeed(0,-1);
        }
    }
}
