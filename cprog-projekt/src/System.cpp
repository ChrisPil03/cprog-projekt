#include "Constants.h"
#include "System.h"
#include <SDL2/SDL.h>

namespace engine{

    System::System(){
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 600, 400, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        TTF_Init();
        font = TTF_OpenFont((constants::gResPath + "fonts/arial.ttf").c_str(), 36);
    }

    SDL_Renderer* System::getRen() const{

        return renderer;
    }

	TTF_Font* System::getFont() const{

        return font;
    }

    System::~System(){
        TTF_CloseFont(font);
        TTF_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
    }
    System system;
}