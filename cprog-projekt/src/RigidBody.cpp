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

    RigidBody::RigidBody(Component* parent, Collider2D* collider, std::string groundTag) : accelerationX(0.3f), accelerateX(false), collider(collider), groundTag(groundTag){
        session.addComponent(this);
        setParent(parent);
    }

//saves last position of parent, if collision is detected, parent is moved back, checks collision with ground.
    void RigidBody::update(){
        const int lastYPos = getParent()->getRect()->y;
        const int lastXPos = getParent()->getRect()->x;
        updateVelocity();
        setParentPosition();
        Collider2D* col = collider->hasCollided(groundTag);
        if (col){
            // Need to call onCollision on the parent to be able to use onCollision to find collision with ground
            // There is probably a better way to do it
            // Becasue this update function makes it so that the collider never outside this function collides with ground
            // getCollision() in collider will never get a collision with ground when collider parent has a RigidBody
            getParent()->onCollision(col);
            verticalCollision(col,lastYPos,lastXPos);
        }else{
            grounded = false;
        }
        col = collider->hasCollided(groundTag);
        if (col){
            horizontalCollision(col,lastXPos);
            col = collider->hasCollided(groundTag);
            if (col){
                verticalCollision(col,lastYPos,lastXPos);
            }
        }
    }

    void RigidBody::verticalCollision(Collider2D* col, int lastYPos, int lastXPos){
        // Check if last position was above the collider collided with
        if (lastYPos + getParent()->getRect()->h <= col->getColliderRect()->y){
            //std::cout<<"Vertical collision above"<<std::endl;
            getParent()->getRect()->y = col->getColliderRect()->y - getParent()->getRect()->h;
            grounded = true;
            bounce();
            return;
        }
        grounded = false;
        // Check if last position was below the collider collided with
        if (lastYPos + (getParent()->getRect()->h - collider->getColliderRect()->h) >= col->getColliderRect()->y + col->getColliderRect()->h &&
            !(lastXPos + ((getParent()-> getRect()->w -collider->getColliderRect()->w)/2) >= col->getColliderRect()->x + col->getColliderRect()->w) &&
            !(lastXPos + (getParent()->getRect()->w - (getParent()-> getRect()->w -collider->getColliderRect()->w)/2) <= col->getColliderRect()->x))
        {
            //std::cout<<"Vertical collision below"<<std::endl;
            getParent()->getRect()->y = col->getColliderRect()->y + col->getColliderRect()->w - (getParent()->getRect()->h - collider->getColliderRect()->h);
            velocityY = 0;
        }
    }

    void RigidBody::horizontalCollision(Collider2D* col, int lastXPos){
        // Check if collider is to the right of the collider collided with
        if(collider->getColliderRect()->x > col->getColliderRect()->x){
            //std::cout<<"Horizontal collision right"<<std::endl;
            getParent()->getRect()->x = col->getColliderRect()->x + col->getColliderRect()->w - ((getParent()-> getRect()->w -collider->getColliderRect()->w)/2);
        }
        // Check if collider is to the left of the collider collided with
        else if (collider->getColliderRect()->x + collider->getColliderRect()->w < col->getColliderRect()->x + col->getColliderRect()->w){
            //std::cout<<"Horizontal collision left"<<std::endl;
            getParent()->getRect()->x = col->getColliderRect()->x - getParent()->getRect()->w + ((getParent()-> getRect()->w - collider->getColliderRect()->w)/2);
        } 
    }

//increases/deacreases lineary to target velocity.
    void RigidBody::updateVelocity(){
        if (!accelerateX){
            velocityX = targetVelocityX;
        }else{
            if (velocityX < targetVelocityX){
                velocityX += accelerationX;
            }
            else if (std::round(velocityX) > targetVelocityX){ //gotta have round
                velocityX -= accelerationX;
            }
        }
        if (velocityY < gravity){
            velocityY += 0.2f;
        }
    }

// sets the position of the parent(sprite)
    void RigidBody::setParentPosition(){
        getParent()->getRect()->y += std::ceil(velocityY);
        getParent()->getRect()->x += velocityX;
    }

    void RigidBody::bounce(){
        if (velocityY > gravity/2){
            velocityY = -velocityY/elasticity;
        }else{
            velocityY = 0;
        }
    }
}