#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "Component.h"
#include "Animation.h"
#include <vector>
#include <string>

namespace engine
{
    class Sprite : public Component
    {
    public:
        ~Sprite();
        static Sprite* getInstance(int x, int y, int w, int h, std::string texture);
        static Sprite* getInstance(int x, int y, int w, int h, Component* animation);

        void render();
        void update();

        void addChild(Component* c);
        SDL_Rect* getRect() { return &rect;}

    protected:
        Sprite(int x, int y, int w, int h, std::string texture);
        Sprite(int x, int y, int w, int h, Component* animation);
    private:
        SDL_Rect rect;
        SDL_Rect frameRect;
        SDL_Texture* texture;
        bool isAnimated = false;
        std::vector<Component*> children;
        Sprite(const Sprite&) = delete;
        const Sprite& operator=(const Sprite&) = delete;
    };
}
#endif