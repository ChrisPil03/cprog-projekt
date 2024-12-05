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

    void RigidBody::addForce(float xForce, float yForce){
        velocityX += xForce;
        velocityY += yForce * -1;
    }

    void RigidBody::setGravity(float gravity){
        this->gravity = gravity;
    }

    void RigidBody::update(){
        int lastYPos = getParent()->getRect()->y;
        int lastXPos = getParent()->getRect()->x;
        updateVelocity();
        if (collider->hasCollided(groundTag) && lastYPos < getParent()->getRect()->y){
            getParent()->getRect()->y = lastYPos;
        }
        if (collider->hasCollided(groundTag) && lastXPos != getParent()->getRect()->x){
            getParent()->getRect()->x = lastXPos;
        }
    }

    void RigidBody::updateVelocity(){
        getParent()->getRect()->y += velocityY;
        getParent()->getRect()->x += velocityX;
    }
}