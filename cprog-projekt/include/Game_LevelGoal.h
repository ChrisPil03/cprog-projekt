#ifndef LEVELGOAL_H
#define LEVELGOAL_H

#include "Sprite.h"
#include "Collider2D.h"

#define BLUE_GOAL "/images/bg.jpg"
#define RED_GOAL "/images/Box.png"
#define GOAL_TAG "Goal"
#define GOAL_WIDTH 48
#define GOAL_HEIGHT 64

namespace game
{
    class LevelGoal : public engine::Sprite
    {
    public:
        static LevelGoal* getInstance(int x, int y, std::string color);
        const std::string getColor(){ return color; }
        void update();
        void checkLevelComplete();
        void completeLevel();
        ~LevelGoal();
    private:
        LevelGoal(int x, int y, std::string color);
        std::string color;
        engine::Collider2D* collider;

        static bool bluePlayerAtGoal;
        static bool redPlayerAtGoal;
    };
}

#endif