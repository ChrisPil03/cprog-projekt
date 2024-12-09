#ifndef MAP_H
#define MAP_H

#include "Component.h"
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include <string>

namespace engine
{
    class Map : public Component
    {
    public:
        static Map* getInstance(std::vector<std::vector<int>> map, std::string tileMap, int sideLength, int tileCount, int scale)
            { return new Map(map, tileMap, sideLength, tileCount, scale); }
        void render();
        ~Map();
    private:
        Map(std::vector<std::vector<int>> map, std::string tileMap, int sideLength, int tileCount, int scale);

        std::vector<std::vector<int>> map;
        SDL_Texture* tileMap;
        int tileSideLength;
        int tiles;
        int scale;
        std::map<int,SDL_Rect*> tileSourceRects;
        SDL_Rect destionationRect;
    };
}

#endif