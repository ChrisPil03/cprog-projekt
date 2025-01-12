#include "Button.h"
#include "Constants.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "System.h"
#include "Sprite.h"

namespace engine{

    Button::Button (int x, int y, int w, int h,std::string imagePath)
    : Sprite(x,y,w,h,imagePath){}

    Button::~Button(){
        SDL_DestroyTexture(txtTexture);
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
}