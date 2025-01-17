#include "Sprite.h"
#include "Constants.h"
#include "System.h"
#include <SDL2/SDL_image.h>

namespace engine
{
    Sprite::Sprite(int x, int y, int w, int h, std::string txt) : rect { x,y,w,h }{
        texture = IMG_LoadTexture(system.getRen(), (constants::gResPath + txt).c_str());
    }

    Sprite* Sprite::getInstance(int x, int y, int w, int h, std::string txt){
        return new Sprite(x,y,w,h, txt);
    }

    // flips sprite to opposite direction.
    void Sprite::flipX(){
        if (directionX == SDL_FLIP_NONE){
            directionX = SDL_FLIP_HORIZONTAL;
        }
        else{
            directionX = SDL_FLIP_NONE;
        }
    }

    Sprite::~Sprite(){
        SDL_DestroyTexture(texture);
    }

    void Sprite::render(){
        SDL_RenderCopyEx(system.getRen(), texture, NULL, &rect, 0, nullptr, directionX);
    }
}