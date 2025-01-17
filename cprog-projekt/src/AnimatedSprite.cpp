#include "AnimatedSprite.h"
#include "Session.h"

namespace engine
{
    AnimatedSprite* AnimatedSprite::getInstance(int x, int y, int w, int h, Animation* animation){
        return new AnimatedSprite(x,y,w,h,animation);
    }

    AnimatedSprite::AnimatedSprite(int x, int y, int w, int h, Animation* animation) : rect{x,y,w,h}{
        addAnimation(animation);
        currentAnimation = animation;
        currentAnimation->play(true);
    }

    void AnimatedSprite::flipX(){
        for(Animation* a : animationList){
            a->flipX();
        }
    }

    void AnimatedSprite::playAnimation(std::string animationName){
        if (currentAnimation->getName() != animationName){
            currentAnimation->play(false);
            for(Animation* animation : animationList){
                if(animation->getName() == animationName){
                    currentAnimation = animation;
                    animation->play(true);
                }
            }  
        }
    }

    void AnimatedSprite::addAnimation(Animation* animation){
        animationList.push_back(animation);
        animation->setParent(this);
    }

    AnimatedSprite::~AnimatedSprite(){
        for(Animation* anim : animationList){
            session.removeComponent(anim);
        }
    }
}