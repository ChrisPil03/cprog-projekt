#include "Game_Player.h"

#include "Animation.h"
#include "Collider2D.h"
#include "RigidBody.h"
#include "Session.h"
#include "Game_Platform.h"

namespace game
{
    Player::Player(int x, int y, int w, int h):
        Sprite(x, y, w, h, engine::Animation::getInstance("Idle", "/images/BlueSlimeIdle.png", 32, 32, 6, 10, true)),
        collider(engine::Collider2D::getInstance(x,y,40,32,"Player")),
        rgdb(engine::RigidBody::getInstance(this, collider, "Ground"))
    {
        collider->setParent(this);
        rgdb->setElasticity(2);
        rgdb->setAccelerateX(true);
        addAnimation(engine::Animation::getInstance("Jump", "/images/BlueSlimeJump.png", 32, 32, 3, 1, false));
        addAnimation(engine::Animation::getInstance("Fall", "/images/BlueSlimeFall.png", 32, 32, 3, 1, false));
    }

    void Player::update(){
        rgdb->targetVelocityX = 0;
        if (engine::session.keyDown("A")){
            rgdb->targetVelocityX = -speed;
            if (!hasFlipped){
                hasFlipped = true;
                flipX();
            }
        }
        if (engine::session.keyDown("D")){
            rgdb->targetVelocityX = speed;
            if (hasFlipped){
                hasFlipped = false;
                flipX();
            }
        }
        if(rgdb->isGrounded()){
            playAnimation("Idle");
            
            if (engine::session.keyDown("W")){
                playAnimation("Jump");
                rgdb->velocityY = jumpForce;
            }
        }else if (onPlatform){
            onPlatform = false;
        }
        if (onPlatform){
            getRect()->x += groundSpeed;
        }
        if (!rgdb->isGrounded() && rgdb->velocityY > 5){
            playAnimation("Fall");
        }
    }

    void Player::onCollision(Component* other){
        if(other->getTag() == "Coin"){
            engine::session.removeComponent(other->getParent());
            engine::session.removeComponent(other);
        }
        if (other->getTag() == "Ground"){
            if (Platform* platform = static_cast<Platform*>(other->getParent())){
                // Needed to not get onPlatform = true when under the platform
                // Not guaranteed that collider is on top of platform with this check
                if (collider->getColliderRect()->y < other->getColliderRect()->y && rgdb->isGrounded()){
                    onPlatform = true;
                    groundSpeed = platform->getSpeed();
                }
            }else{
                onPlatform = false;
                groundSpeed = 0;
            }
        }
    }

    Player::~Player(){
        engine::session.removeComponent(collider);
        engine::session.removeComponent(rgdb);
    }
}