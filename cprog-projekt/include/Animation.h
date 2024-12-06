#ifndef ANIMATION_H
#define ANIMATION_H

#include "Component.h"
#include <string>

namespace engine{
    class Animation : public Component
    {
    public:
        static Animation* getInstance(std::string animationName, std::string spriteSheet, int frameWidth, int frameHeigth, int frameCount, int animationSpeed);
        ~Animation();
        //void render();
        void flipX();
        const std::string getName(){return animationName;} // const!!!!
        void play();
    private:
        std::string animationName;
        SDL_Texture* spriteSheet;
        int frameW;
        int frameH;
        int frames;
        int speed; // Higher speed = slower animation
        SDL_Rect frameRect;
        SDL_RendererFlip directionX = SDL_FLIP_NONE;

        Animation(std::string animationName, std::string spriteSheet, int frameWidth, int frameHeigth, int frameCount, int animationSpeed);
    };
}

#endif