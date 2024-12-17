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

    RigidBody::RigidBody(Component* parent, Collider2D* collider, std::string groundTag) : accelerateX(false), collider(collider), groundTag(groundTag){
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
            if(col->getIsStatic() || lastYPos + getParent()->getRect()->h <= col->getColliderRect()->y || 
                col->getColliderRect()->y + col->getColliderRect()->h < lastYPos + getParent()->getRect() ->h - collider->getColliderRect()->h){

                getParent()->getRect()->x = lastXPos;
            }
            else{
                if(collider->getColliderRect()->x > col->getColliderRect()->x){
                    getParent()->getRect()->x = col->getColliderRect()->x + col->getColliderRect()->w -((getParent()-> getRect()->w -collider->getColliderRect()->w)/2);
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
        if (!accelerateX){
            velocityX = targetVelocityX;
        }else{
            if (velocityX < targetVelocityX){
                velocityX += 0.2f;
            }
            else if (std::round(velocityX) > targetVelocityX){ //gotta have round
                velocityX -= 0.2f;
            }
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