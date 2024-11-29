#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "Component.h"
#include <string>

namespace engine
{
    class Sprite : public Component
    {
    public:
        ~Sprite();
        static Sprite* getInstance(int x, int y, int w, int h, std::string texture); 

        void render() const;
        void update();
        SDL_Rect* getRect() { return &rect;}

    protected:
        Sprite(int x, int y, int w, int h, std::string texture);
    private:
        SDL_Rect rect;
        SDL_Texture* texture;
        Sprite(const Sprite&) = delete;
        const Sprite& operator=(const Sprite&) = delete;
    };
}
#endif