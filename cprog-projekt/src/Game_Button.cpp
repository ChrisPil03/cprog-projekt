#include "Game_Button.h"
#include "Session.h"

namespace game {

    Button* Button::getInstance(int x, int y, int w, int h, Platform* platform) {
        return new Button(x, y, w, h, platform);
    }

    Button::Button(int x, int y, int w, int h, Platform* platform) : engine::Sprite(x, y, w, h, BUTTON_NORMAL),
        buttonPressed(false), platform(platform)
    {
        collider = engine::Collider2D::getInstance(x, y, w, h, "Button");
        collider->setParent(this);
        platform->setIsControlled(true);
    }

    void Button::update(){
        if(collider->hasCollided("Player")){
            if (!buttonPressed){
                changeTexture(BUTTON_PRESSED);
                buttonPressed = true;
            }
            platform->setSpeed(0,1);
        }else{
            if(buttonPressed){
                changeTexture(BUTTON_NORMAL);
                buttonPressed = false;
            }
        }
    }

    Button::~Button(){
        engine::session.removeComponent(collider);
    }
}