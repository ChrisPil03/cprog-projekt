#include "Animation.h" 
#include "System.h"
#include "Constants.h"
#include "Session.h"
#include <string>
#include <SDL2/SDL_image.h>
 
namespace engine{

    Animation* Animation::getInstance(std::string animationName, std::string spriteSheetPath, int frameWidth, int frameHeigth, int frameCount, int animationSpeed){
        return new Animation(animationName, spriteSheetPath, frameWidth, frameHeigth, frameCount, animationSpeed);
    }

    Animation::Animation(std::string animationName, std::string spriteSheetPath, int frameWidth, int frameHeigth, int frameCount, int animationSpeed):
        animationName(animationName), spriteSheet(IMG_LoadTexture(system.getRen(), (constants::gResPath + spriteSheetPath).c_str())), 
        frameW(frameWidth), frameH(frameHeigth), frames(frameCount), speed(animationSpeed), frameRect{0,0, frameWidth, frameHeigth}
    {
        session.addComponent(this);  
    }

    //moves sourcerect, when counter is evenly divisible by speed the rendered part of the spritesheet is moved to the next, if you are at the end of the spritesheet it will reset to 0.
    void Animation::play(){ 
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

// flips the sprite to face the opposit direction
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