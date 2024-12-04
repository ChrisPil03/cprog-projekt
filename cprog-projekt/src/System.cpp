#include "Constants.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace engine{

    System::System(){
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 960, 640, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        TTF_Init();
        font = TTF_OpenFont((constants::gResPath + "fonts/arial.ttf").c_str(), 36);
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