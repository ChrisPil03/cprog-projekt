#ifndef ANIMATION_H
#define ANIMATION_H

#include "Component.h"

namespace engine{
    class Animation : public Component
    {
    public:
        static Animation* getInstance(std::string animationName, std::string spriteSheet, int frameWidth, int frameHeigth, int frameCount, int animationSpeed, bool loop);
        ~Animation();
        void render();
        void flipX();
        std::string getName() const { return animationName; }
        void play(bool play) { playAnimation =  play; }
    private:
        std::string animationName;
        SDL_Texture* spriteSheet;
        SDL_Rect frameRect;
        int frames;
        int speed; // Higher speed = slower animation
        bool loop;
        bool playAnimation = false;
        int currentFrame = 0;
        int counter = 0;
        SDL_RendererFlip directionX = SDL_FLIP_NONE;

        Animation(std::string animationName, std::string spriteSheet, int frameWidth, int frameHeigth, int frameCount, int animationSpeed, bool loop);
    };
}

#endif