#include "RigidBody.h"
#include "Session.h"

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
        getParent()->getRect()->y += gravity;
        if (collider->hasCollided("Ground")){
            getParent()->getRect()->y -= gravity;
        }
    }
}