#include "Sprite.h"
#include "Constants.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

namespace engine
{
    Sprite::Sprite(int x, int y, int w, int h, std::string txt) : rect { x,y,w,h }{
        texture = IMG_LoadTexture(system.getRen(), (constants::gResPath + txt).c_str());
    }

    Sprite::Sprite(int x, int y, int w, int h, std::string txt, int frameCount, int xF) : rect {x,y,w,h}, frameRect {0,0,xF,xF} ,frames(frameCount), xFrame(xF){
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
            static int counter = 0;
            counter++;
            if (counter % 10 == 0){
                static int frame = 0;
                frameRect.x = xFrame * frame;
                frame++;
                if (frame >= frames){
                    frame = 0;
                }
            }
            SDL_RenderCopy(system.getRen(), texture, &frameRect, &rect);
        }
        else{
		    SDL_RenderCopy(system.getRen(), texture, NULL, &rect);
        }
	}
}