#ifndef WATER_H
#define WATER_H

#include "Sprite.h"
#include "Collider2D.h"

#define BLUE_WATER "/images/bg.jpg"
#define RED_WATER "/images/Box.png"
#define TAG "Water"

namespace game
{
    class Water : public engine::Sprite
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