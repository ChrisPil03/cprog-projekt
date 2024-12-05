#ifndef COLLIDER2D_H
#define COLLIDER2D_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <string>

namespace engine{
    class Collider2D : public Component
    {
    public:
        static Collider2D* getInstance(int x, int y, int w, int h, std::string tag);

        bool hasCollided(std::string tagName);
        const std::string getTag() const { return tag; }
        const SDL_Rect* getColliderRect() const { return &collider; }
        void updateCollider();
    private:
        Collider2D(int x, int y, int w, int h, std::string tag);

        SDL_Rect collider;
        std::string tag;
    };
}

#endif