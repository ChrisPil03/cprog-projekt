#include "Sprite.h"
#include "Constants.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace engine
{
    Sprite::Sprite(int x, int y, int w, int h) : rect { x,y,w,h }{
        texture = IMG_LoadTexture(system.getRen(), (constants::gResPath + "images/bg.jpg").c_str());

    }

    Sprite* Sprite::getInstance(int x, int y, int w, int h){
        return new Sprite(x,y,w,h);
    }

    void Sprite::update(){

    }

    void Sprite::moveRight(){
        rect.x++;
    }

    void Sprite::moveLeft(){
        rect.x--;
    }

    void Sprite::moveUp(){
        rect.y--;
    }

    void Sprite::moveDown(){
        rect.y++;
    }

    Sprite::~Sprite(){
        SDL_DestroyTexture(texture);
    }

    void Sprite::render() const {

		SDL_RenderCopy(system.getRen(), texture, NULL, &rect);

	}
}