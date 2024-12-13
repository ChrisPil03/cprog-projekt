#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <SDL2/SDL.h>

namespace engine{
    class Component
    {
    public:
        virtual ~Component(){}
        virtual void render(){}
        virtual void update(){}
        virtual const std::string getTag() const{ return "";}
        virtual const SDL_Rect* getColliderRect() const{ return nullptr;}
        virtual SDL_Rect* getRect(){return nullptr;}
        virtual void onCollision(Component* other){}

        void setParent(Component* parent) { this->parent = parent; }
        Component* getParent() { return parent; }

    protected:
        Component() : parent(nullptr){}

    private:
        Component* parent;
        Component(const Component&) = delete;            
        const Component* operator=(const Component&) = delete;
    };
}

#endif