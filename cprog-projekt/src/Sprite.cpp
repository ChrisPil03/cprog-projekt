#include "Sprite.h"

namespace gameEngine
{
    Sprite::Sprite(int x, int y, int w, int h) : rect { x,y,w,h }{}

    Sprite::~Sprite(){}
}