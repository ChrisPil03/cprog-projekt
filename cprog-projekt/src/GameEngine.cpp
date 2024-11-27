#include "Constants.h"
#include "GameEngine.h"
#include <SDL2/SDL.h>

namespace gameEngine
{
    GameEngine::GameEngine(){
        SDL_Init(SDL_INIT_EVERYTHING);
        win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN);
        ren = SDL_CreateRenderer(win, -1, 0);
        TTF_Init();
        font = TTF_OpenFont((constants::gResPath + "fonts/arial.ttf").c_str(), 36);
    }

    SDL_Renderer* GameEngine::getRen() const{
        return ren;
    }
    
    TTF_Font* GameEngine::getFont() const{
        return font;
    }

    void GameEngine::add(Sprite* sprite){
        added.push_back(sprite);
    }

    void GameEngine::remove(Sprite* sprite){
        removed.push_back(sprite);
    }

    void GameEngine::setFPS(int newFps){
        fps = newFps;
    }

    void GameEngine::run(){
        bool quit = false;
        Uint32 tickInterval = 1000 / fps;
        while (!quit){
            SDL_Event eve;
            while (SDL_PollEvent(&eve)){
                switch (eve.type){
                case SDL_QUIT: quit = true; break;
                case SDL_KEYDOWN:
                    for (Sprite* s : sprites){
                        s->keyDown(eve);
                    }
                case SDL_KEYUP:{
                    for (Sprite* s : sprites){
                        s->keyUP(eve);
                    }
                }
                case SDL_MOUSEBUTTONDOWN:
                    for (Sprite* s : sprites){
                        s->mouseDown(eve);
                    }
                case SDL_MOUSEBUTTONUP:
                    for (Sprite* s : sprites){
                        s->mouseUp(eve);
                    }
                } // switch
            } // inre while

            for (Sprite* s : sprites){
                s->update();
            }

            for (Sprite* s : added){
                sprites.push_back(s);
            }
            added.clear();

            for (Sprite* s : removed){
                for (std::vector<Sprite*>::iterator iter = sprites.begin(); iter != sprites.end();){
                    if (*iter == s){
                        delete *iter;
                        iter = sprites.erase(s);
                    }
                    else{
                        iter++;
                    }
                }
            }
            removed.clear();

        } // yttre while
    }

    GameEngine::~GameEngine(){
        TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		SDL_Quit();
    }
}