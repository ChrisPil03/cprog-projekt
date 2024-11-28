#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "Component.h"

namespace engine
{
    class Sprite : public Component
    {
    public:
        ~Sprite();
        static Sprite* getInstance(int x, int y, int w, int h); 

        void render() const;
        void update();

    protected:
        Sprite(int x, int y, int w, int h);
    private:
        SDL_Rect rect;
        //SDL_Texture* texture;
        Sprite(const Sprite&) = delete;
        const Sprite& operator=(const Sprite&) = delete;
    };
}
#endif