#include "Sprite.h"
#include "Constants.h"
#include "System.h"
#include "Animation.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

namespace engine
{
    Sprite::Sprite(int x, int y, int w, int h, std::string txt) 
        : rect { x,y,w,h }{
        texture = IMG_LoadTexture(system.getRen(), (constants::gResPath + txt).c_str());
    }

    Sprite::Sprite(int x, int y, int w, int h, Component* animation) 
        : rect {x,y,w,h}{
        children.push_back(animation);
        isAnimated = true;
    }

    Sprite* Sprite::getInstance(int x, int y, int w, int h, std::string txt){
        return new Sprite(x,y,w,h, txt);
    }

    Sprite* Sprite::getInstance(int x, int y, int w, int h, Component* animation){
        return new Sprite(x,y,w,h, animation);
    }

    void Sprite::update(){
        
    }

    void Sprite::addChild(Component* c){
        children.push_back(c);
        c->addParent(this);


    }

    Sprite::~Sprite(){
        SDL_DestroyTexture(texture);
        
        for (std::vector<Component*>::iterator iter = children.begin(); iter != children.end();){
            delete *iter;
            iter = children.erase(iter);
        }
    }

  
  void Sprite::render(){
    if(!isAnimated){
        SDL_RenderCopy(system.getRen(), texture, NULL, &rect);
    }
}
   
	
}