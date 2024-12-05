#include "Collider2D.h"
#include "session.h"
#include <string>
#include <iostream>

namespace engine{
    Collider2D* Collider2D::getInstance(int x, int y, int w, int h, std::string tagName){
        return new Collider2D(x,y,w,h,tagName);
    }

    Collider2D::Collider2D(int x, int y, int w, int h, std::string tagName):
        collider {x,y,w,h}, tag(tagName)
    {
        session.addComponent(this);
    }

    bool Collider2D::hasCollided(std::string tagName){
        updateCollider();
        for (Component* c : session.getComponents()){
            std::string cTag = c->getTag();
            if (cTag == tagName && c != this){
                if(SDL_HasIntersection(&collider, c->getColliderRect())){
                    return true;
                }
            }
        }
        return false;
    }

    void Collider2D::updateCollider(){
        collider.x = getParent()->getRect()->x + ((getParent()-> getRect()->w - collider.w)/2);
        collider.y = getParent()->getRect()->y + (getParent()->getRect()->h - collider.h);
    }
}