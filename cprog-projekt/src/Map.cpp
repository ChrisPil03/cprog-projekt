#include "Map.h"
#include <SDL2/SDL_image.h>
#include "Constants.h"
#include "System.h"
#include "Session.h"
#include <vector>
#include <iostream>


namespace engine{
    Map::Map(std::vector<std::vector<int>> map, std::string tileMap, int sideLength, int tileCount, int scale) :
        map(map), tileMap(IMG_LoadTexture(system.getRen(),(constants::gResPath + tileMap).c_str())),
        tileSideLength(sideLength), tiles(tileCount), scale(scale), destionationRect{0,0,tileSideLength*scale,tileSideLength*scale}
    {
        //session.addComponent(this);

        for (int i = 0; i < tiles; i++){
            tileSourceRects[i+1] = new SDL_Rect {i*sideLength, 0, sideLength, sideLength};
        }
    }

    void Map::render(){
        for (std::vector vec : map){
            for (int tileID : vec){
                if (tileID > 0 && tileID <= tiles){
                    SDL_RenderCopy(system.getRen(), tileMap, tileSourceRects[tileID], &destionationRect);
                }
                destionationRect.x += (tileSideLength*scale);
            }
            destionationRect.x = 0;
            destionationRect.y += (tileSideLength*scale);
        }
        destionationRect.y = 0;
    }

    Map::~Map(){
        SDL_DestroyTexture(tileMap);
        // Delete SDL_Rect* in tileSourceRects
    }
}