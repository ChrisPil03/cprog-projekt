#include "Animation.h" 
#include "System.h"
#include "Constants.h"
#include "Session.h"
#include <string>
#include <SDL2/SDL_image.h>
 
 namespace engine{

    Animation::Animation(std::string spriteSheetLink, int frameCount, int frameW)
        :spriteSheet(IMG_LoadTexture(system.getRen(), (constants::gResPath + spriteSheetLink).c_str())), 
        frames(frameCount), frameWidth(frameW), frameRect{0,0, frameW, frameW}{
           session.addComponent(this);  
    }
    void Animation::addParent(Component* c){
        parent = c;
    }

    void Animation::render(){
        
        static int counter = 0;
        counter++;
        if (counter % 10 == 0){
            static int frame = 0;
            frameRect.x = frameWidth * frame;
            frame++;
            if (frame >= frames){
                frame = 0;
            }             
        }
        SDL_RenderCopy(system.getRen(), spriteSheet, &frameRect, parent->getRect());
    }

    Animation::~Animation(){
        delete parent;
        SDL_DestroyTexture(spriteSheet);
    }
 }
