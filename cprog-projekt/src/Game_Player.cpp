#include "Game_Player.h"

#include "Animation.h"
#include "Collider2D.h"
#include "RigidBody.h"
#include "Session.h"
#include "Game_Platform.h"

#define Witdh {64}
#define Height {64}

namespace game
{
    Player::Player(int x, int y, std::string moveLeftKey, std::string moveRightKey, std::string jumpKey):
        Sprite(x, y, Witdh, Height, engine::Animation::getInstance("Idle", "/images/BlueSlimeIdle.png", 32, 32, 6, 10, true)),
        collider(engine::Collider2D::getInstance(x,y,40,32,"Player")),
        rgdb(engine::RigidBody::getInstance(this, collider, "Ground")),
        moveLeftKey(moveLeftKey), moveRightKey(moveRightKey), jumpKey(jumpKey)
    {
        collider->setParent(this);
        rgdb->setElasticity(2);
        rgdb->setAccelerateX(true);
        addAnimation(engine::Animation::getInstance("Jump", "/images/BlueSlimeJump.png", 32, 32, 3, 1, false));
        addAnimation(engine::Animation::getInstance("Fall", "/images/BlueSlimeFall.png", 32, 32, 3, 1, false));
    }

    void Player::update(){
        rgdb->targetVelocityX = 0;

        if(rgdb->isGrounded()){
            playAnimation("Idle");
        }else if (onPlatform){
            onPlatform = false;
        }

        handleInputs();
        
        if (onPlatform){
            getRect()->x += groundSpeed;
        }
        if (!rgdb->isGrounded() && rgdb->velocityY > 5){
            playAnimation("Fall");
        }
    }

    void Player::handleInputs(){
        if (engine::session.keyDown(moveLeftKey)){
            rgdb->targetVelocityX = -speed;
            if (!hasFlipped){
                hasFlipped = true;
                flipX();
            }
        }
        if (engine::session.keyDown(moveRightKey)){
            rgdb->targetVelocityX = speed;
            if (hasFlipped){
                hasFlipped = false;
                flipX();
            }
        }
        if (rgdb->isGrounded()){
            if (engine::session.keyDown(jumpKey)){
                rgdb->velocityY = jumpForce;
                playAnimation("Jump");
            }
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