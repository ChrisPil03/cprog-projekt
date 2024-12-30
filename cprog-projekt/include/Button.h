#ifndef BUTTON_H
#define BUTTON_H

#include "Sprite.h"
#include <SDL2/SDL.h>
#include <string>

namespace engine{

    class Button : public Sprite{
    public:
        static Button* getInstance(int x, int y, int w, int h, std::string txt, std::string imagePath);
        static Button* getInstance(int x, int y, int w, int h, std::string imagePath);
        void mouseDown (const SDL_Event&);
        void mouseUp(const SDL_Event&);
        void render();
        virtual void execute(Button* source){}
        ~Button();

    protected:
        Button(int x, int y, int w, int h, std::string txt, std::string imagePath);
        Button(int x, int y, int w, int h, std::string imagePath);

    private: 
        std::string text;
        SDL_Texture* txtTexture;
        bool isDown = false;
    };
}

#endif