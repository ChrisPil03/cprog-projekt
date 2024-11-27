#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "Sprite.h"

namespace gameEngine
{
    class GameEngine
    {
        public:
            GameEngine();
            SDL_Renderer* getRen() const;
            TTF_Font* getFont() const;
            void add(Sprite* sprite);
            void remove(Sprite* sprite);
            void setFPS(int fps);
            void run();
            ~GameEngine();
        private:
            SDL_Window* win;
		    SDL_Renderer* ren;
		    TTF_Font* font;
            std::vector<Sprite*> sprites;
            std::vector<Sprite*> added, removed;
            int fps = 60;
    };
    extern GameEngine gameEngine;
}
#endif