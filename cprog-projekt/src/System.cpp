#include "Constants.h"
#include "System.h"
#include <SDL2/SDL.h>

namespace engine{

    System::System(){
        SDL_Init(SDL_INIT_EVERYTHING);
        win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN);
        ren = SDL_CreateRenderer(win, -1, 0);
        TTF_Init();
        font = TTF_OpenFont((constants::gResPath + "fonts/arial.ttf").c_str(), 36);
    }
}