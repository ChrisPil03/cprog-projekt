#include "Game_Player.h"

#include "Animation.h"
#include "Collider2D.h"
#include "RigidBody.h"
#include "Session.h"
#include "Game_Platform.h"
#include "Game_GameManager.h"
#include "Component.h"
#include "Game_Water.h"
#include <iostream>

namespace game
{
    Player* Player::getInstance(int x, int y, std::string moveLeftKey, std::string moveRightKey, std::string jumpKey,
        std::string color)
    {
        return new Player(x,y,moveLeftKey,moveRightKey,jumpKey,color);
    }

    Player::Player(int x, int y, std::string moveLeftKey, std::string moveRightKey, std::string jumpKey,
        std::string color) :
        AnimatedSprite(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, engine::Animation::getInstance("Idle", (color == "Blue") ? BLUE_IDLE_ANIM : RED_IDLE_ANIM, 32, 32, 6, 10, true)),
        collider(engine::Collider2D::getInstance(x,y,40,32,"Player")),
        rgdb(engine::RigidBody::getInstance(this, collider, "Ground")),
        spawnPointX(x), spawnPointY(y),
        moveLeftKey(moveLeftKey), moveRightKey(moveRightKey), jumpKey(jumpKey), color(color)
    {
        collider->setParent(this);
        rgdb->setElasticity(2);
        rgdb->setAccelerateX(true);
        if (color == "Blue"){
            addAnimation(engine::Animation::getInstance("Jump", BLUE_JUMP_ANIM, 32, 32, 3, 1, false));
            addAnimation(engine::Animation::getInstance("Fall", BLUE_FALL_ANIM, 32, 32, 3, 1, false));
        }else{
            addAnimation(engine::Animation::getInstance("Jump", RED_JUMP_ANIM, 32, 32, 3, 1, false));
            addAnimation(engine::Animation::getInstance("Fall", RED_FALL_ANIM, 32, 32, 3, 1, false)); 
        }
    }

    void Player::update(){
        rgdb->setTargetVelocityX(0);

        if(rgdb->isGrounded()){
            playAnimation("Idle");
        }else if (onPlatform){
            onPlatform = false;
        }

        handleInputs();
        
        if (onPlatform){
            getRect()->x += groundSpeedX;
        }
        if (!rgdb->isGrounded() && rgdb->getVelocityY() > 5){
            playAnimation("Fall");
        }
    }

    void Player::handleInputs(){
        if (engine::session.keyDown(moveLeftKey)){
            relSpeed = -speed;
            rgdb->setTargetVelocityX(relSpeed);
            if (!hasFlipped){
                hasFlipped = true;
                flipX();
            }
        }
        if (engine::session.keyDown(moveRightKey)){
            relSpeed = speed;
            rgdb->setTargetVelocityX(relSpeed);
            if (hasFlipped){
                hasFlipped = false;
                flipX();
            }
        }
        if (rgdb->isGrounded()){
            if (engine::session.keyDown(jumpKey)){
                rgdb->setVelocityY(jumpForce);
                playAnimation("Jump");
            }
        }
    }

    void Player::onCollision(Component* other){
        if(other->getTag() == "Gem"){
            std::cout << "Colliding with gem" << std::endl;
            engine::session.removeComponent(other->getParent());
            GameManager::collectGem();
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
        if(other->getTag() == "Box"){
            other->getParent()->getRect()->x += relSpeed;
        }
        if(other->getTag() == "Water"){
            if (Water* water = dynamic_cast<Water*>(other->getParent())){
                if (this->getColor() != water->getColor()){
                    respawn();
                }
            }
        }
    }

    void Player::respawn(){
        rgdb->setTargetVelocityX(0);
        rgdb->setVelocityX(0);
        rgdb->setVelocityY(0);
        getRect()->x = spawnPointX;
        getRect()->y = spawnPointY;
    }

    Player::~Player(){
        engine::session.removeComponent(collider);
        engine::session.removeComponent(rgdb);
    }
}