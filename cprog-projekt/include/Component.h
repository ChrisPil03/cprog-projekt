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
        virtual void addParent(Component* c){}
        virtual SDL_Rect* getRect(){return nullptr;}

    protected:
        Component(){}

    private:
        Component(const Component&) = delete;            
        const Component* operator=(const Component&) = delete;
    };
}

#endif