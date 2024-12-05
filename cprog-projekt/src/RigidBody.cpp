#include "RigidBody.h"
#include "Session.h"
#include <iostream>
#include <string>

namespace engine
{
    RigidBody::RigidBody(Component* parent, Collider2D* collider, std::string groundTag) : collider(collider), groundTag(groundTag){
        session.addComponent(this);
        setParent(parent);
    }

    void RigidBody::addForce(int xForce, int yForce){
        targetVelocityX += xForce;
        targetVelocityY += yForce * -1;
    }

    void RigidBody::setGravity(int gravity){
        this->gravity = gravity;
    }

    void RigidBody::update(){
        int lastYPos = getParent()->getRect()->y;
        int lastXPos = getParent()->getRect()->x;
        updateVelocity();
        setParentPosition();
        if (collider->hasCollided(groundTag)){
            getParent()->getRect()->y = lastYPos;
            grounded = true;
        }
        else{
            grounded = false;
        }
        if (collider->hasCollided(groundTag)){
            getParent()->getRect()->x = lastXPos;
        }
    }

    void RigidBody::updateVelocity(){
        if (velocityX < targetVelocityX){
            velocityX += 0.5;
        }
        else if (velocityX > targetVelocityX){
            velocityX -= 0.5;
        }
        if (velocityY < targetVelocityY){
            velocityY += 0.5;
        }
        else if (velocityY > targetVelocityY){
            velocityY -= 0.5;
        }
        else{
            targetVelocityY = gravity;
        }
    }

    void RigidBody::setParentPosition(){
        getParent()->getRect()->y += velocityY;
        getParent()->getRect()->x += velocityX;
    }
}