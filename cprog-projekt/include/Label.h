#ifndef LABEL_H
#define LABEL_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <string>

namespace engine
{
    class Label : public Component
    {
    public:
        static Label* getInstance(int x, int y, int w, int h, std::string text);
        void render();
        void setText(std::string newText);
        std::string getText() const { return text; }
        SDL_Rect* getRect() { return &rect; }
        ~Label();
    protected:
        Label(int x, int y, int w , int h, std::string text);
    private:
        void createTexture();
        std::string text;
        SDL_Rect rect;
        SDL_Texture* texture;
    };
}

#endif