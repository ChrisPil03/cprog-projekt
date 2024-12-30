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

        Collider2D* hasCollided(std::string tagName);
        const std::string getTag() const { return tag; }
        const SDL_Rect* getColliderRect() const { return &collider; }
        void updateCollider();
        void update();
        Component* getCollision();
        void setStatic(bool isStatic){this->isStatic = isStatic;}
        bool getIsStatic(){ return isStatic; }
        void setJumpThrought(bool jumpThrough){ this->jumpThrough = jumpThrough; }
        const bool getJumpThrough(){ return jumpThrough; }

        ~Collider2D(){}

    private:
        Collider2D(int x, int y, int w, int h, std::string tag);

        SDL_Rect collider;
        std::string tag;
        bool isStatic;
        bool jumpThrough;
    };
}

#endif