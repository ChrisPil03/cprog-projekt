#include "Session.h"
#include "Sprite.h"
#include "Component.h"
//#include <SDL2/SDL.h>

using namespace engine;

int main (int argc, char** argv){

   Sprite* testSprite = Sprite::getInstance(100, 100, 100, 100);
   session.addComponent(testSprite);
   session.run();

    return 0;
}