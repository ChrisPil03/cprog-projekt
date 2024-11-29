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

    Sprite* Sprite::getInstance(int x, int y, int w, int h, std::string txt){
        return new Sprite(x,y,w,h, txt);
    }

    void Sprite::update(){
        
    }

    Sprite::~Sprite(){
        SDL_DestroyTexture(texture);
    }

    void Sprite::render() const {

		SDL_RenderCopy(system.getRen(), texture, NULL, &rect);

	}
}