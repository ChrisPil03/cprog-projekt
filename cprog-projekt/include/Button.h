#ifndef BUTTON_H
#define BUTTON_H

#include "Sprite.h"

namespace engine
{
    class Button : public Sprite
    {
    public:
        static Button* getInstance(int x, int y, int w, int h, std::string imagePath);
        void mouseDown (const SDL_Event&);
        void mouseUp(const SDL_Event&);
        virtual void execute(Button* source){}
        ~Button();

    protected:
        Button(int x, int y, int w, int h, std::string imagePath);

    private: 
        bool isDown = false;
    };
}

#endif