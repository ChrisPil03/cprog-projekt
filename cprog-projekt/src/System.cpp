#include "Constants.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

namespace engine{

    System::System(){
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 960, 640, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        TTF_Init();
        font = TTF_OpenFont((constants::gResPath + "fonts/arial.ttf").c_str(), 36);
        SDL_SetRenderDrawColor(system.getRen(), 255, 255, 255, 255);
        Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
    }

    System::~System(){
        TTF_CloseFont(font);
        TTF_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
        Mix_CloseAudio();
		SDL_Quit();
    }

    System system;
}