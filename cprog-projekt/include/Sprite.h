#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "Component.h"
#include <vector>
#include <string>

namespace engine{
    class Sprite : public Component
    {
    public:
        static Sprite* getInstance(int x, int y, int w, int h, std::string texture);
        void render();
        void flipX();
        void changeTexture(std::string imagePath);
        SDL_Rect* getRect() { return &rect;}
        void mouseDown(const SDL_Event&) {}
		void mouseUp(const SDL_Event&) {}
        ~Sprite();

    protected:
        Sprite(int x, int y, int w, int h, std::string texture);
        void onCollision(Component* other){}

    private:
        SDL_Rect rect;
        SDL_Texture* texture;
        SDL_RendererFlip directionX = SDL_FLIP_NONE;
    };
}
#endif