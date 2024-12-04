#include "Animation.h" 
#include "System.h"
#include "Constants.h"
#include "Session.h"
#include <string>
#include <SDL2/SDL_image.h>
 
namespace engine{

    Animation* Animation::getInstance(std::string spriteSheetPath, int frameWidth, int frameHeigth, int frameCount, int animationSpeed){
        return new Animation(spriteSheetPath, frameWidth, frameHeigth, frameCount, animationSpeed);
    }

    Animation::Animation(std::string spriteSheetPath, int frameWidth, int frameHeigth, int frameCount, int animationSpeed):
        spriteSheet(IMG_LoadTexture(system.getRen(), (constants::gResPath + spriteSheetPath).c_str())), 
        frameW(frameWidth), frameH(frameHeigth), frames(frameCount), speed(animationSpeed), frameRect{0,0, frameWidth, frameHeigth}
    {
        session.addComponent(this);  
    }

    void Animation::render(){ 
        static int counter = 0;
        counter++;
        if (counter % speed == 0){
            static int frame = 0;
            frameRect.x = frameW * frame;
            frame++;
            if (frame >= frames){
                frame = 0;
            }             
        }
        SDL_RenderCopyEx(system.getRen(), spriteSheet, &frameRect, getParent()->getRect(), 0, nullptr, directionX);
    }

    void Animation::flipX(){
        if (directionX == SDL_FLIP_NONE)
            directionX = SDL_FLIP_HORIZONTAL;
        else
            directionX = SDL_FLIP_NONE;
    }

    Animation::~Animation(){
        SDL_DestroyTexture(spriteSheet);
    }
}