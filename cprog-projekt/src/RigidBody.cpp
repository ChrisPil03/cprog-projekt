#include "RigidBody.h"
#include "Session.h"
#include <iostream>

namespace engine
{
    RigidBody::RigidBody(Component* parent, Collider2D* collider) : gravity(2.0f), collider(collider){
        session.addComponent(this);
        setParent(parent);
    }

    void RigidBody::addForce(float xForce, float yForce){

    }

    void RigidBody::setGravity(float gravity){
        this->gravity = gravity;
    }

    void RigidBody::update(){
        updateVelocity();
        velocityY = gravity;
        if (collider->hasCollided("Ground")){
            velocityY = 0;
        }       
    }

    void RigidBody::updateVelocity(){
        getParent()->getRect()->y += velocityY;
        getParent()->getRect()->x += velocityX;
    }
}