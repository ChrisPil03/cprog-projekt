#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Component.h"
#include "Animation.h"
#include <vector>

namespace engine
{
    class AnimatedSprite : public Component
    {
    public:
        static AnimatedSprite* getInstance(int x, int y, int w, int h, Animation* animation);
        void flipX();
        void playAnimation(std::string animationName);
        void addAnimation(Animation* animation);
        SDL_Rect* getRect() { return &rect;}
        ~AnimatedSprite();
    protected:
        AnimatedSprite(int x, int y, int w, int h, Animation* animation);
    private:
        void onCollision(Component*){}

        SDL_Rect rect;
        Animation* currentAnimation;
        std::vector<Animation*> animationList;
    };
}

#endif