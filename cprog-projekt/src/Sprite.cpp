#include "Sprite.h"
#include "Constants.h"
#include "System.h"
#include "Animation.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

namespace engine
{
    Sprite::Sprite(int x, int y, int w, int h, std::string txt) : rect { x,y,w,h }{
        texture = IMG_LoadTexture(system.getRen(), (constants::gResPath + txt).c_str());
    }

    Sprite::Sprite(int x, int y, int w, int h, Animation* animation) 
        : rect {x,y,w,h}, animation(animation){
        animation->setParent(this);
        isAnimated = true;
    }

    Sprite* Sprite::getInstance(int x, int y, int w, int h, std::string txt){
        return new Sprite(x,y,w,h, txt);
    }

    Sprite* Sprite::getInstance(int x, int y, int w, int h, Animation* animation){
        return new Sprite(x,y,w,h, animation);
    }

    void Sprite::flipX(){
        if(!isAnimated)
            if (directionX == SDL_FLIP_NONE)
                directionX = SDL_FLIP_HORIZONTAL;
            else
                directionX = SDL_FLIP_NONE;
        else
            animation->flipX();
    }

    Sprite::~Sprite(){
        SDL_DestroyTexture(texture);
    }

    void Sprite::render(){
        if(!isAnimated){
            SDL_RenderCopyEx(system.getRen(), texture, NULL, &rect, 0, nullptr, directionX);
        }
    }
}