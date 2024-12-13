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

//looks through component list after a matching tag to the parameter, if a component has a matching tag and is not the same instance, hasCollided will return true.
    bool Collider2D::hasCollided(std::string tagName){
        updateCollider();
        for (Component* c : session.getComponents()){ // only colliders, not comps
            std::string cTag = c->getTag();
            if (cTag == tagName && c != this){
                if(SDL_HasIntersection(&collider, c->getColliderRect())){
                    return true;
                }
            }
        }
        return false;
    }
//updates collider position to the same as the parent bottom center.
    void Collider2D::updateCollider(){
        if(getParent()){
            collider.x = getParent()->getRect()->x + ((getParent()-> getRect()->w - collider.w)/2);
            collider.y = getParent()->getRect()->y + (getParent()->getRect()->h - collider.h);
        }
 
    }

    void Collider2D::update(){
        if(getParent() && getCollision()){
            getParent()->onCollision(getCollision());
        }
    }

    Component* Collider2D::getCollision(){
        for (Component* c : session.getComponents()){ 
            if (c != this && c-> getColliderRect()){
                if(SDL_HasIntersection(&collider, c->getColliderRect())){
                    return c;
                }
            }
        }
        return nullptr;
    }

}