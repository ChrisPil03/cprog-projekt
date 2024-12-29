#include "Map.h"
#include <SDL2/SDL_image.h>
#include "Constants.h"
#include "System.h"
#include "Session.h"
#include <vector>
#include <string>
#include "Collider2D.h"
#include "Game_Pickup.h"
#include <iostream>


namespace engine{
    Map::Map(std::vector<std::vector<int>> map, std::string tileMap, int sideLength, int tileCount, int scale, std::string tag) :
        map(map), tileMap(IMG_LoadTexture(system.getRen(),(constants::gResPath + tileMap).c_str())),
        tileSideLength(sideLength), tiles(tileCount), scale(scale), tag(tag), destinationRect{0,0,tileSideLength*scale,tileSideLength*scale}
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
                    SDL_RenderCopy(system.getRen(), tileMap, tileSourceRects[tileID], &destinationRect);
                    if(!collidersCreated){
                        Collider2D* temp = Collider2D::getInstance(destinationRect.x,destinationRect.y,tileSideLength*scale,tileSideLength*scale,tag);
                        tileColliders.push_back(temp);
                        temp-> setStatic(true);
                    }
                }
                if(tileID == -1 && !pickupsCreated){
                    game::Pickup* coin = game::Pickup::getInstance(destinationRect.x,destinationRect.y,16,16,"/images/GoldCoin.png","Coin");
                    engine::session.addComponent(coin);
                }
                destinationRect.x += (tileSideLength*scale);
            }
            destinationRect.x = 0;
            destinationRect.y += (tileSideLength*scale);
        }
        destinationRect.y = 0;
        collidersCreated = true;
        pickupsCreated = true;
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