#include "Collider2D.h"
#include "session.h"
#include <string>
#include <iostream>

namespace engine{
    Collider2D::Collider2D(int x, int y, int w, int h, Sprite* sprite, std::string tagName) 
        : collider {x,y,w,h}, tag(tagName), belongsTo(sprite){ session.addComponent(this); }

    bool Collider2D::hasCollided(std::string tagName){
        updateCollider();
        for (Component* c : session.getComponents()){
            std::string cTag = c->getTag();
            if (cTag == tagName && c != belongsTo){ // funkar c != belongsTo?
                if(SDL_HasIntersection(&collider, c->getColliderRect())){
                    return true;
                }
            }
        }
        return false;
    }

    void Collider2D::update(){}

    void Collider2D::updateCollider(){
        collider.x = belongsTo->getRect()->x + ((belongsTo-> getRect()->w - collider.w)/2);
        collider.y = belongsTo->getRect()->y + (belongsTo->getRect()->h - collider.h);
    }
}