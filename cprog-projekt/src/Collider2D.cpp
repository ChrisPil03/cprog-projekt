#include "Collider2D.h"
#include "session.h"
#include <string>

namespace engine{
    Collider2D::Collider2D(int x, int y, int w, int h, Sprite* sprite, std::string tagName) : collider {x,y,w,h}, tag(tagName), belongsTo(sprite){ session.addComponent(this); }

    bool Collider2D::hasCollided(std::string tagName){
        for (Component* c : session.getComponents()){
            std::string cTag = c->getTag();
            if (cTag == tagName && c != belongsTo){ // funkar c != belongsTo?
                return SDL_HasIntersection(&collider, c->getColliderRect());
            }
        }
        return false;
    }

    void Collider2D::update(){
        collider.x = belongsTo->getRect()->x + ((belongsTo->getRect()->w - collider.w) / 2);
        collider.y = belongsTo->getRect()->y + (belongsTo->getRect()->h - collider.h);
    }
}