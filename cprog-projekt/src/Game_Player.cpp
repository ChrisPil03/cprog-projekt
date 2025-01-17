#include "Game_Player.h"

#include "Animation.h"
#include "Collider2D.h"
#include "RigidBody.h"
#include "Session.h"
#include "Game_Platform.h"
#include "Component.h"

#define Witdh {64}
#define Height {64}

namespace game
{
    Player* Player::getInstance(int x, int y, std::string moveLeftKey, std::string moveRightKey, std::string jumpKey,
        std::string idleAnimPath, std::string jumpAnimPath, std::string fallAnimPath)
    {
        return new Player(x,y,moveLeftKey,moveRightKey,jumpKey,idleAnimPath,jumpAnimPath,fallAnimPath);
    }

    Player::Player(int x, int y, std::string moveLeftKey, std::string moveRightKey, std::string jumpKey,
    std::string idleAnimPath, std::string jumpAnimPath, std::string fallAnimPath):
        AnimatedSprite(x, y, Witdh, Height, engine::Animation::getInstance("Idle", idleAnimPath, 32, 32, 6, 10, true)),
        collider(engine::Collider2D::getInstance(x,y,40,32,"Player")),
        rgdb(engine::RigidBody::getInstance(this, collider, "Ground")),
        moveLeftKey(moveLeftKey), moveRightKey(moveRightKey), jumpKey(jumpKey)
    {
        collider->setParent(this);
        rgdb->setElasticity(2);
        rgdb->setAccelerateX(true);
        addAnimation(engine::Animation::getInstance("Jump", jumpAnimPath, 32, 32, 3, 1, false));
        addAnimation(engine::Animation::getInstance("Fall", fallAnimPath, 32, 32, 3, 1, false));
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
            getRect()->x += groundSpeedX;
        }
        if (!rgdb->isGrounded() && rgdb->velocityY > 5){
            playAnimation("Fall");
        }
    }

    void Player::handleInputs(){
        if (engine::session.keyDown(moveLeftKey)){
            relSpeed = -speed;
            rgdb->targetVelocityX = relSpeed;
            if (!hasFlipped){
                hasFlipped = true;
                flipX();
            }
        }
        if (engine::session.keyDown(moveRightKey)){
            relSpeed = speed;
            rgdb->targetVelocityX = relSpeed;
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
        if(other->getTag() == "Gem"){
            engine::session.removeComponent(other->getParent());
        }
        if (other->getTag() == "Ground"){
            if (Platform* platform = dynamic_cast<Platform*>(other->getParent())){
                // Needed to not get onPlatform = true when under the platform
                // Not guaranteed that collider is on top of platform with this check
                if (collider->getColliderRect()->y < other->getColliderRect()->y && rgdb->isGrounded()){
                    onPlatform = true;
                    groundSpeedX = platform->getSpeedX();
                }
            }else{
                onPlatform = false;
                groundSpeedX = 0;
            }
        }
        if(other-> getTag() == "Box"){
            other->getParent()->getRect()->x += relSpeed;
        }
    }

    Player::~Player(){
        engine::session.removeComponent(collider);
        engine::session.removeComponent(rgdb);
    }
}