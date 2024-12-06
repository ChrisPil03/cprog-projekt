#include "RigidBody.h"
#include "Session.h"
#include <iostream>
#include <string>

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
        if (collider->hasCollided(groundTag)){
            getParent()->getRect()->x = lastXPos;
        }
        if (collider->hasCollided(groundTag)){
            getParent()->getRect()->y = lastYPos;
            bounce();
            grounded = true;
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