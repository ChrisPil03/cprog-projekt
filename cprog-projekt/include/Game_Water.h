#ifndef WATER_H
#define WATER_H

#include "AnimatedSprite.h"
#include "Collider2D.h"

#define BLUE_WATER "/images/BlueWater.png"
#define RED_WATER "/images/RedWater.png"
#define TAG "Water"

namespace game
{
    class Water : public engine::AnimatedSprite
    {
    public:
        static Water* getInstance(int x, int y, int w, int h, std::string color);
        const std::string getColor(){ return color; }
        ~Water();
    private:
        Water(int x, int y, int w, int h, std::string color);
        std::string color;
        engine::Collider2D* collider;
    };
}

#endif