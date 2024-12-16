#include "RigidBody.h"
#include "Session.h"
#include "Collider2D.h"
#include <iostream>
#include <string>
#include "Component.h"

namespace engine
{
    RigidBody* RigidBody::getInstance(Component* parent, Collider2D* collider, std::string groundTag){
        return new RigidBody(parent,collider,groundTag);
    }

    RigidBody::RigidBody(Component* parent, Collider2D* collider, std::string groundTag) : collider(collider), groundTag(groundTag){
        session.addComponent(this);
        setParent(parent);
    }

//saves last position of parent, if collision is detected, parent is moved back, checks collision with ground.
    void RigidBody::update(){
        int lastYPos = getParent()->getRect()->y;
        int lastXPos = getParent()->getRect()->x;
        updateVelocity();
        setParentPosition();
        Collider2D* col = collider->hasCollided(groundTag);
        if (col){
           
           if(col->getIsStatic()||collider->getColliderRect()->y + collider->getColliderRect()->h < col->getColliderRect()->y  || 
                col->getColliderRect()->y + col->getColliderRect()->h < collider->getColliderRect()->y){
                getParent()->getRect()->x = lastXPos;
           }
           else{
                if(collider->getColliderRect()->x > col->getColliderRect()->x){

                //  std::cout<< "expected: " << comp->getColliderRect()->x + comp->getColliderRect()->w << std::endl;

                    getParent()->getRect()->x = col->getColliderRect()->x + col->getColliderRect()->w -((getParent()-> getRect()->w -collider->getColliderRect()->w)/2);
                    
                //    std::cout<< "actual: "<< getParent()->getRect()->x << std::endl;
                }
                else{
                    getParent()->getRect()->x = col -> getColliderRect()->x - getParent()->getRect()->w +((getParent()-> getRect()->w -collider->getColliderRect()->w)/2);
                }   
           }
        }
        col = collider->hasCollided(groundTag);
        if (col){
            if (lastYPos < getParent()->getRect()->y){
                grounded = true;
            }
            if(collider->getColliderRect()->y > col->getColliderRect()->y){
                //getParent()->getRect()->y = comp->getColliderRect()->y + comp->getColliderRect()->h;
                getParent()->getRect()->y = lastYPos;
            } else{
                getParent()->getRect()->y = col -> getColliderRect()->y - getParent()->getRect()->h;
            }
    
            bounce();
        }
        else{
            grounded = false;
        }

        
    }

//increases/deacreases lineary to target velocity.
    void RigidBody::updateVelocity(){
        if (velocityX < targetVelocityX){
            velocityX += 0.2f;
        }
        else if (std::round(velocityX) > targetVelocityX){ //gotta have round
            velocityX -= 0.2f;
        }
        if (velocityY < gravity){
            velocityY += 0.2f;
        }
    }

// sets the position of the parent(sprite)
    void RigidBody::setParentPosition(){
        getParent()->getRect()->y += velocityY;
        getParent()->getRect()->x += velocityX;
    }

    void RigidBody::bounce(){
        if (velocityY > gravity/2){
            velocityY = -velocityY/elasticity;
        }else{
            velocityY = 0; // HUH
        }
    }
}