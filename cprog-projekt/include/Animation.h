#ifndef ANIMATION_H
#define ANIMATION_H

#include "Component.h"
#include "Sprite.h"
#include <string>


namespace engine{
    class Animation : public Component{

    public:
        Animation(std::string spriteSheet, int frames, int frameWidth);
        ~Animation();
        void addParent(Component* c);
        void render();



    private:
        SDL_Texture* spriteSheet;
        int frames;
        int frameWidth;
        SDL_Rect frameRect;
        Component* parent;

    };


}


#endif