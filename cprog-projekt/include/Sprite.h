#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "Component.h"
#include "Animation.h"
#include <vector>
#include <string>

namespace engine{
    class Sprite : public Component
    {
    public:
        ~Sprite();
        static Sprite* getInstance(int x, int y, int w, int h, std::string texture);
        static Sprite* getInstance(int x, int y, int w, int h, Animation* animation);
        void render();
        void flipX();
        void playAnimation(std::string animationName);
        SDL_Rect* getRect() { return &rect;}
        void addAnimation(Animation* a){  a->setParent(this); animationList.push_back(a);}
        protected:
        Sprite(int x, int y, int w, int h, std::string texture);
        Sprite(int x, int y, int w, int h, Animation* animation);
    private:
        SDL_Rect rect;
        SDL_Texture* texture;
        SDL_RendererFlip directionX = SDL_FLIP_NONE;
        bool isAnimated = false;
        //Animation* animation;
        std::vector<Animation*> animationList;
    };
}
#endif