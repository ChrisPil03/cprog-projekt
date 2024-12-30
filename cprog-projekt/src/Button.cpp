#include "Button.h"
#include "Constants.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "System.h"

namespace engine{

    Button::Button (int x, int y, int w, int h, std::string txt, std::string imagePath)
    : Sprite(x,y,w,h,imagePath){
        SDL_Surface* surf = TTF_RenderText_Solid(system.getFont(), txt.c_str(), { 0,0,0 });
		txtTexture = SDL_CreateTextureFromSurface(system.getRen(), surf);
		SDL_FreeSurface(surf);
    }

    Button::Button (int x, int y, int w, int h,std::string imagePath)
    : Sprite(x,y,w,h,imagePath){}

    Button::~Button(){
        SDL_DestroyTexture(txtTexture);
    }

    Button* Button::getInstance(int x, int y, int w, int h, std::string txt, std::string imagePath){
        return new Button(x,y,w,h,txt,imagePath);
    }
    Button* Button::getInstance(int x, int y, int w, int h, std::string imagePath){
        return new Button(x,y,w,h,imagePath);
    }

	void Button::mouseDown(const SDL_Event& eve) {
		SDL_Point p = { eve.button.x, eve.button.y };
		if (SDL_PointInRect(&p, getRect()))
			isDown = true;
	}
	void Button::mouseUp(const SDL_Event& eve) {
		SDL_Point p = { eve.button.x, eve.button.y };
		if (SDL_PointInRect(&p, getRect()))
			execute(this);

		isDown = false;
	}

    void Button::render() {

        if(txtTexture){
            SDL_RenderCopy(system.getRen(), txtTexture, NULL, getRect());
        }
	}

}