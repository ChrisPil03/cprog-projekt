#include "Map.h"
#include <SDL2/SDL_image.h>
#include "Constants.h"
#include "System.h"
#include "Session.h"
#include <vector>
#include <string>
#include "Collider2D.h"
#include <iostream>


namespace engine{
    Map::Map(std::vector<std::vector<int>> map, std::string tileMap, int sideLength, int tileCount, int scale, std::string tag) :
        map(map), tileMap(IMG_LoadTexture(system.getRen(),(constants::gResPath + tileMap).c_str())),
        tileSideLength(sideLength), tiles(tileCount), scale(scale), tag(tag), destionationRect{0,0,tileSideLength*scale,tileSideLength*scale}
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
                    if(!collidersCreated){
                        tileColliders.push_back(Collider2D::getInstance(destionationRect.x,destionationRect.y,tileSideLength*scale,tileSideLength*scale,tag));
                    }
                }
                destionationRect.x += (tileSideLength*scale);
            }
            destionationRect.x = 0;
            destionationRect.y += (tileSideLength*scale);
        }
        destionationRect.y = 0;
        collidersCreated = true;
    }

    Map::~Map(){
        SDL_DestroyTexture(tileMap);

        // Delete colliders
        for (std::vector<Collider2D*>::iterator iter = tileColliders.begin(); iter != tileColliders.end();){
            session.removeComponent(*iter);
            iter = tileColliders.erase(iter);
        }
           
        // Delete SDL_Rect* in tileSourceRects
    }
}