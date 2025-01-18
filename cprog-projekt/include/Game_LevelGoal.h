#ifndef LEVELGOAL_H
#define LEVELGOAL_H

#include "Sprite.h"
#include "Collider2D.h"

#define BLUE_GOAL_CLOSED "/images/BlueDoor_Closed.png"
#define BLUE_GOAL_OPEN "/images/BlueDoor_Open.png"
#define RED_GOAL_CLOSED "/images/RedDoor_Closed.png"
#define RED_GOAL_OPEN "/images/RedDoor_Open.png"
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
        void closeDoors();
        std::string color;
        engine::Collider2D* collider;

        inline static bool levelComplete;
        inline static bool bluePlayerAtGoal;
        inline static bool redPlayerAtGoal;
    };
}

#endif