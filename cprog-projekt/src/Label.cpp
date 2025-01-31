#include "Label.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"

namespace engine
{
    Label* Label::getInstance(int x, int y, int w, int h, std::string text){
        return new Label(x,y,w,h,text);
    }

    Label::Label(int x, int y, int w, int h, std::string text) : text(text), rect{x,y,w,h} {
        createTexture();
    }

    void Label::render(){
        SDL_RenderCopy(system.getRen(), texture, NULL, getRect());
    }

    void Label::setText(std::string newText){
        text = newText;
        SDL_DestroyTexture(texture);
        createTexture();
    }

    void Label::createTexture(){
        SDL_Surface* surf = TTF_RenderText_Solid(system.getFont(), text.c_str(), {255,255,255});
        texture = SDL_CreateTextureFromSurface(system.getRen(), surf);
        SDL_FreeSurface(surf);
    }

    Label::~Label(){
        SDL_DestroyTexture(texture);
    }
}