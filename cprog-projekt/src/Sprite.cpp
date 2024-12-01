#include "Sprite.h"
#include "Constants.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

namespace engine
{
    Sprite::Sprite(int x, int y, int w, int h, std::string txt) : rect { x,y,w,h }{
        texture = IMG_LoadTexture(system.getRen(), (constants::gResPath + txt).c_str());
    }

    Sprite::Sprite(int x, int y, int w, int h, std::string txt, int frameCount, int xFrame) : rect {x,y,w,h}, frameRect {0,0,xFrame,xFrame} ,frames(frameCount){
        texture = IMG_LoadTexture(system.getRen(), (constants::gResPath + txt).c_str());
        isAnimated = true;
    }

    Sprite* Sprite::getInstance(int x, int y, int w, int h, std::string txt){
        return new Sprite(x,y,w,h, txt);
    }

    Sprite* Sprite::getInstance(int x, int y, int w, int h, std::string txt, int frames, int xFrame){
        return new Sprite(x,y,w,h,txt,frames,xFrame);
    }

    void Sprite::update(){
        
    }

    Sprite::~Sprite(){
        SDL_DestroyTexture(texture);
    }

    void Sprite::render(){
        if (isAnimated){
            int frame = 0;
            if (frame <= frames){
                frame++;
            } else{
                frame = 1;
            }
            frameRect.x = xFrame * frame;
            SDL_RenderCopy(system.getRen(), texture, &frameRect, &rect);
        }
        else{
		    SDL_RenderCopy(system.getRen(), texture, NULL, &rect);
        }
	}
}