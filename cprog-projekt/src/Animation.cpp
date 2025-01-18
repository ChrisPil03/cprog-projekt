#include "Animation.h" 
#include "System.h"
#include "Constants.h"
#include "Session.h"
#include <string>
#include <SDL2/SDL_image.h>
 
namespace engine{

    Animation* Animation::getInstance(std::string animationName, std::string spriteSheetPath, int frameWidth, int frameHeigth, int frameCount, int animationSpeed, bool loop){
        return new Animation(animationName, spriteSheetPath, frameWidth, frameHeigth, frameCount, animationSpeed, loop);
    }

    Animation::Animation(std::string animationName, std::string spriteSheetPath, int frameWidth, int frameHeigth, int frameCount, int animationSpeed, bool loop):
        animationName(animationName), spriteSheet(IMG_LoadTexture(system.getRen(), (constants::gResPath + spriteSheetPath).c_str())), 
        frameRect{0,0, frameWidth, frameHeigth}, frames(frameCount), speed(animationSpeed), loop(loop)
    {
        session.addComponent(this);  
    }

    //moves sourcerect, when counter is evenly divisible by speed the rendered part of the spritesheet is moved to the next, if you are at the end of the spritesheet it will reset to 0.
    void Animation::render(){
        if (getParent()){
            if (playAnimation){
                counter++;
                if (counter % speed == 0){ 
                    frameRect.x = frameRect.w * currentFrame;
                    currentFrame++;
                    if (currentFrame == frames){
                        loop ? currentFrame = 0 : currentFrame = frames - 1;
                    }      
                }
                SDL_RenderCopyEx(system.getRen(), spriteSheet, &frameRect, getParent()->getRect(), 0, nullptr, directionX);
            } else{
                // when animation stops playing the counters are reset, next time the animation plays it will start fresh 
                if (currentFrame != 0){
                    currentFrame = 0;
                    counter = 0;
                }
            }
        }
    }

// flips the sprite to face the opposite direction
    void Animation::flipX(){
        if (directionX == SDL_FLIP_NONE){
            directionX = SDL_FLIP_HORIZONTAL;
        } else{
            directionX = SDL_FLIP_NONE;
        }
    }

    Animation::~Animation(){
        SDL_DestroyTexture(spriteSheet);
    }
}